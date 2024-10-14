#ifndef WORLD_HPP
#define WORLD_HPP

#include "Worldgen/Chunk.hpp"
#include <thread>

namespace WorldGen
{
	#define CHUNKS_NUM 4
	#define THREADS_NUM_DEFAULT 8
	#define TIME_GEN_CHUNKS

	class World
	{
	public:
		World();
		~World();

		// must be run in a thread
		void generateChunks();
		void Update();

#ifdef TIME_GEN_CHUNKS
		void checkGenFinnished();
#endif

		void Draw();
	private:
		static unsigned int getLogicalThreads();

		Chunk chunks[CHUNKS_NUM][CHUNKS_NUM];
		std::vector<std::thread> threads;
		std::thread chunksThread;
		unsigned int numThreads;
		bool finnishedGen = false;

#ifdef TIME_GEN_CHUNKS
		std::chrono::steady_clock::time_point startTime;
		bool time_gen_bool;
#endif
	};
} // namespace WorldGen

#endif //WORLD_HPP
