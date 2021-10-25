import json, multiprocessing, datetime
#import pdb; pdb.set_trace()

from time import time, sleep
from influxdb_client import InfluxDBClient, Point, WritePrecision
from influxdb_client.client.write_api import SYNCHRONOUS

if __name__ == '__main__':
	pass
else : 
	pass

class End_Device(Log_Writer,Guard):
	TOKEN = "K_w-a8zb3ontSnIdNpH7gnQlgjlrXJbX8KJ04wcF1p-N0u5lafF7GEkrhznCUVxwzyKVR6awcuDT5mbMJRvBhg=="
	INFLUX_URL = "https://us-east-1-1.aws.cloud2.influxdata.com"
	ORG = "delapanbelasa@gmail.com"
	BUCKET = "test_python"
	

	def __init__(self,**kwargs):
		#print("MRO:", [x.__name__ for x in End_Device.__mro__])
		super(End_Device, self).__init__(**kwargs)
		self.high_count = 0
		self.low_count = 0
		self.last_influx = 0
		self.reading = kwargs["device_reading"]
		self.name = kwargs["device_name"]
		self.InfluxClient = InfluxDBClient(url=self.INFLUX_URL, token=self.TOKEN)
		self.write_api = self.InfluxClient.write_api(write_options=SYNCHRONOUS)
		self.decontamination_progress = 0
		self.six_log_progress = 0

	def send_influx(self,**kwargs):
		"""sending influx data using class method"""		
		name = kwargs["device_name"]
		count = kwargs["device_count"]		
		timestamp = str(time())
		timestamps = timestamp.split(".")
		timestamp = timestamps[0]+timestamps[1]+"00"
		self.dataToInflux = f'movement,host={name} activity_meter={count},decontam_percentage={self.decontamination_progress:.2f}' #,six_log={100*self.six_log_progress:.2f}'# {timestamp}'

		try :
			start = time()
			if self.six_log_progress <= 2.0:
				self.write_api.write(self.BUCKET, self.ORG, self.dataToInflux)							
				print(f'DB Rspd: {time()-start:.2f}s {name} prog:{self.decontamination_progress:.2f}, cont:{count}')
				#self.last_influx = time()
			else:
				print(f'ilegal value six_log_progress:{self.six_log_progress:.1f}')				
		except Exception:
			print("some problem in sending DB")
			print(Exception.with_traceback())
			pass
		

	@classmethod
	def from_string(cls, device_string):
		"""konfersi dict-like sting ke python dict"""
		json_object = json.loads(device_string)
		for key in json_object:
			device_name = key
			device_reading = json_object[key]
		return device_name, device_reading
	
	def counting_value(self,reading, is_purging):
		self.reading = reading
		self.is_purging = is_purging	
		"""Oprasi penambahan/pengurangan value device's sensor berdasarkan sensor reading"""
		if self.reading.lower() == "low":			
			if is_purging == True:
				self.low_count += 1
				print("masuk calc purg")
				self.chek_cleaning_time(self.low_count)
			
			if is_purging == False:
				print("auto set pct prg to 0")
				self.low_count = 0
				self.decontamination_progress = 0
			

		if self.reading.lower() == "high":
			if self.count <= 512:
				self.high_count += 1
			self.last_cek = 0 #dari class sterile_clac
			if is_purging == True:
				#self.chek_cleaning_time(self.high_count)
				self.decontamination_progress = 0
				self.low_count = 0
				print("tirgged Purge in HIGH")
			if is_purging == False:
				self.decontamination_progress = 0

		
			
		print(f'is_purging : {is_purging}   low_count:{self.low_count}')
		
		
		#print(f'last DB: {time()-self.last_influx} count:{self.high_count}             ', end = "\r")
		# sending count every 1 minute to infux
		if time()-self.last_influx >= 10 or self.last_influx == 0:			
			Write_Job = multiprocessing.Process(target=self.update_log)				
			Querying_Job = multiprocessing.Process(target=self.send_influx, kwargs={"device_name":self.name,"device_count":self.high_count})#, "decontamination_progress":decontamination_progress, "six_log_progress":six_log_progress})
			
			
			if time()-self.last_influx >= 60 : #or self.last_influx == 0:	
				print(f'reset h count triged {self.name}')
				#reset count value
				self.high_count = 0
				#self.low_count = 0
			self.last_influx = time()
			Write_Job.start()
			Querying_Job.start()