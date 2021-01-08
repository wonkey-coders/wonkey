/// @file
/// @version 2.0
/// 
/// @section LICENSE
/// 
/// This program is free software; you can redistribute it and/or modify it under
/// the terms of the BSD license: http://opensource.org/licenses/BSD-3-Clause
/// 
/// @section DESCRIPTION
/// 
/// Defines a thread.

#ifndef THEORAPLAYER_THREAD_H
#define THEORAPLAYER_THREAD_H

namespace theoraplayer
{
	/// @brief Provides functionality of a Thread for multithreading.
	/// @note Based on hltypes::Thread.
	class Thread
	{
	public:
		/// @brief Internal utility class.
		class ThreadRunner
		{
		public:
			friend class Thread;

			/// @brief Destructor.
			~ThreadRunner();

			/// @return Associated thread.
			inline Thread* getThread() const { return this->thread; }

			/// @return Execute the thread's code.
			void execute();

		protected:
			/// @return Associated thread.
			Thread* thread;

			/// @brief Constructor.
			/// @param[in] thread Associated thread.
			ThreadRunner(Thread* thread);

		};

		/// @brief Basic constructor.
		/// @param[in] function Function pointer for the callback.
		Thread(void(*function)(Thread*));
		/// @brief Destructor.
		virtual ~Thread();

		/// @brief Gets the current function.
		/// @return The current function.
		inline void (*getFunction())(Thread*) { return this->function; }
		/// @brief Sets function.
		/// @param[in] value New function.
		inline void setFunction(void(*value)(Thread*)) { this->function = value; }
		/// @brief Gets whether this Thread was started.
		/// @return True if this Thread was started.
		inline bool isRunning() const { return this->running; }
		/// @brief Gets whether the thread is executing right now.
		/// @return True if the thread is executing right now.
		inline bool isExecuting() const { return this->executing; }

		/// @brief Starts the thread processing.
		void start();
		/// @brief Stops the thread processing.
		void stop();
		/// @brief Resumes the thread processing.
		void resume();
		/// @brief Pauses the thread processing.
		void pause();
		/// @brief Joins thread.
		void join();
		/// @brief Puts current thread to sleep.
		/// @param[in] milliseconds How long to sleep in milliseconds.
		static void sleep(float milliseconds);

	protected:
		/// @brief Flag that determines whether the thread is executing right now.
		volatile bool executing;

	private:
		/// @brief Utility for running the thread.
		ThreadRunner runner;
		/// @brief The callback function of the thread.
		void (*function)(Thread*);
		/// @brief The internal OS handle ID for the thread.
		void* id;
		/// @brief Flag that determines whether this Thread was started.
		volatile bool running;

		/// @brief Copy constructor.
		/// @note Usage is not allowed and it will throw an exception.
		Thread(const Thread& other);
		/// @brief Assignment operator.
		/// @note Usage is not allowed and it will throw an exception.
		Thread& operator=(Thread& other);

		/// @brief Executes the thread's function.
		void _execute();
		/// @brief Clears thread data.
		void _clear();
		/// @brief Starts the thread processing.
		void _platformStart();
		/// @brief Stops the thread processing.
		void _platformStop();
		/// @brief Resumes the thread processing.
		void _platformResume();
		/// @brief Pauses the thread processing.
		void _platformPause();
		/// @brief Joins thread.
		void _platformJoin();

	};
}

/// @brief Alias for simpler code.
typedef theoraplayer::Thread hthread;

#endif
