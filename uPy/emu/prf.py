# todo: check if .process_time_ns()  is available
import time
import sys

if sys.implementation.name == 'micropython':
  def time_us(): return time.ticks_us()
else:
  def time_us(): return time.process_time_ns()/1000


class Profiler:
  def __init__(self, name="root"):
    self.id = name
    self.reset()

  def reset(self):
    self.t_start = 0
    self.t_min = float("inf")
    self.t_max = 0
    self.t_avg = 0
    self.t_total = 0
    self.nSamples = 0

  def start(self):
    self.t_start = time_us() 

  def stop(self):
    dt = time_us() - self.t_start
    self.t_min = dt if dt < self.t_min else self.t_min
    self.t_max = dt if self.t_max < dt else self.t_max
    self.t_total += dt
    self.nSamples += 1    

  def __str__(self):
    t_avg = self.t_total/self.nSamples/1e6
    t_min=self.t_min/1e6
    t_max=self.t_max/1e6
    return "{}-Profile: {} calls, (min ≤ avg ≤ max) = {}s ≤ {}s ≤ {}s".format(self.id, self.nSamples, t_min, t_avg, t_max)
