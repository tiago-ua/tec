#!/usr/bin/env python
import os
import time
import random
import string
import multiprocessing  # the module we will be using for multiprocessing


def work(Run):
	#NEvents=1000000
	WORKING_DIRECTORY=os.getcwd()
	#randSeed=random.randint(0,32766)
	resultsFile="AmberTarget_Run_"+str(Run)+".root"
	#print(resultsFile)
	os.system("root -l -q DetEneHist.C\(\\\""+resultsFile+"\\\"\)")
	os.system("root -l -q ParticleEnergy.C\(\\\"" + resultsFile + "\\\"\)")
	os.system("root -l -q ZMomentum.C\(\\\"" + resultsFile + "\\\"\)")
	os.system("root -l -q ZPionsMomentum.C\(\\\"" + resultsFile + "\\\"\)")
	os.system("root -l -q analysis.C\(\\\"" + resultsFile + "\\\"\)")
	os.system("root -l -q soma_de_energia_4_particulas.C\(\\\"" + resultsFile + "\\\"\)")
	os.system("root -l -q hadronicVertex.odt\(\\\"" + resultsFile + "\\\"\)")
	os.system("root -l -q hits_distribution_x_y.c\(\\\"" + resultsFile + "\\\"\)")
	os.system("root -l -q vertex.c\(\\\"" + resultsFile + "\\\"\)")
	
	#os.system("mkdir "+resultsFile)
	#os.system("cp "+WORKING_DIRECTORY+"/MultipleFibbers "+resultsFile)
	#os.system("cp "+WORKING_DIRECTORY+"/*.mac "+resultsFile)
	#os.system("cp "+WORKING_DIRECTORY+"/TRITIUMSpectrumNew.txt "+resultsFile)
	#os.chdir(WORKING_DIRECTORY+"/"+resultsFile)
	#os.system("./AmberTarget "+str(Run)+" 0")
	#os.system("mv *.root "+WORKING_DIRECTORY+"/DATA/")
	#os.system("mv output*.txt "+WORKING_DIRECTORY+"/OUTPUTS/")
	#os.chdir(WORKING_DIRECTORY)
	#os.system("rm -rf "+resultsFile)
	print ("Unit of work number %d" % Run ) # simply print the worker's number
	#Analise.C(WORKING_DIRECTORY)

if __name__ == "__main__":  # Allows for the safe importing of the main module
	print("There are %d CPUs on this machine" % multiprocessing.cpu_count())
	#os.system("mkdir DATA")
	#os.system("mkdir OUTPUTS")
	number_processes = multiprocessing.cpu_count()-1
	pool = multiprocessing.Pool(number_processes)
	total_tasks = 4
	tasks = range(total_tasks)
	results = pool.map_async(work, tasks)
	pool.close()
	pool.join()
