/*
 * Option 2: The "Worker Pool" (Professional Way)
 
 In real-world applications, you don't want to wait for all threads to finish before starting new ones. Instead, you use a shared work queue or Producer-Consumer model.
 
     The Producer (Main Thread): Reads chunks from the file and puts them into a "to-do" list (queue).
 
     The Consumers (Worker Threads): Stay alive for the entire duration of the program. They grab a chunk from the queue, count the characters, and then go back to the queue for another chunk.
 
     The Tool: You would use a Mutex and a Condition Variable to make sure two threads don't grab the same chunk at the same time.
 */