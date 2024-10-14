#include "WorldGen/World.hpp"

#define TIME_WORLD_GEN

namespace WorldGen
{
	World::World()
		: numThreads(getLogicalThreads())
	{
		std::cout << "World :: Number of threads: " << numThreads << std::endl;
		std::cout << "World :: Generating " << CHUNKS_NUM << "x" << CHUNKS_NUM << " = " << CHUNKS_NUM * CHUNKS_NUM << " chunks" << std::endl;
		std::cout << "World :: Chunk size x=" << Chunk::size.x << " y=" << Chunk::size.y << " z=" << Chunk::size.z << std::endl;

		chunksThread = std::thread(&World::generateChunks, this);
	}

	World::~World()
	{
		std::cout << "World destroyed" << std::endl;

		chunksThread.join();
	}

	void World::Update()
	{
		for (auto & chunkArr : chunks) {
			for (auto & chunk : chunkArr) {
				if (chunk.genAtom.load() && !chunk.vaoCreated)
					chunk.createVAO();
			}
		}
	}

	void World::generateChunks()
	{
		std::mutex mtx;
		std::condition_variable cv;
		std::atomic activeThreads(0);
		auto base_pos = glm::vec3(-CHUNKS_NUM * Chunk::size.x / 2 , 0, -CHUNKS_NUM * Chunk::size.z / 2);

#ifdef TIME_GEN_CHUNKS
		time_gen_bool = false;
		startTime = std::chrono::high_resolution_clock::now();;
#endif


		for (int i = 0; i < CHUNKS_NUM; i++) {
			for (int j = 0; j < CHUNKS_NUM; j++) {
				threads.emplace_back([this, &mtx, &cv, &activeThreads, i, j, &base_pos]() {
					{
						std::unique_lock lock(mtx);
						while (activeThreads.load() >= numThreads) {
							cv.wait(lock); // Wait if we've reached the max active threads
						}
						++activeThreads; // Increment the count of active threads
					}

					// Generate the chunk
					chunks[i][j].gen(base_pos + glm::vec3(i * Chunk::size.x, 0, j * Chunk::size.z));

					{
						std::unique_lock lock(mtx);
						--activeThreads; // Decrement the count of active threads
						cv.notify_one(); // Notify one waiting thread if any
					}
				});
			}
		}

		// Join all threads after generation
		for (auto & thread : threads) {
			if (thread.joinable()) {
				thread.join();
			}
		}

		threads.clear(); // Clear the thread vector if needed for future use
		finnishedGen = true;
	}

	unsigned int World::getLogicalThreads()
	{
		unsigned int numThreadsTemp = std::thread::hardware_concurrency();
		// Defaults threads to THREADS_NUM_DEFAULT if hardware_concurrency returns 0
		if (numThreadsTemp == 0)
		{
			std::cout << "Could not detect number of threads, defaulting to " << THREADS_NUM_DEFAULT << std::endl;
			numThreadsTemp = THREADS_NUM_DEFAULT;
		} else
			/* if we add one more thread it performs better */
			numThreadsTemp++;
		return numThreadsTemp;
	}

	void World::Draw()
	{
		for (auto & chunkArr : chunks) {
			for (auto & chunk : chunkArr) {
				chunk.Draw();
			}
		}
	}

#ifdef TIME_GEN_CHUNKS
	void World::checkGenFinnished()
	{
		if (finnishedGen && !time_gen_bool)
		{
			time_gen_bool = true;
			const auto endTime = std::chrono::high_resolution_clock::now();
			const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
			std::cout << "World :: Generation time: " << duration.count() << " ms" << std::endl;
		}
	}
#endif
} // namespace WorldGen
