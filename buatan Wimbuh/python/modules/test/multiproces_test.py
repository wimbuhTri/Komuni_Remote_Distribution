import concurrent.futures
import time

start = time.perf_counter()

def do_something(seconds):
	print(f'sleeping for {seconds} seconds')
	time.sleep(seconds)
	print("done sleeping")

processes = []

for _ in range(10):
	p = multiprocessing.Process(target=do_something, args=[1.5])
	p.start()
	processes.append(p)

for process in processes:
	process.join()

finish = time.perf_counter()
print(f'finish in {finish} seconds')