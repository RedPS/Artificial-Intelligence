"""
Pedram Safaei
Project[2] Kalman Filter
CS482
"""
import numpy as np
import math
from scipy import stats
import scipy.stats

def kf_update(u, sigma, z):
	deltaT = 1
	x = 6
	S_z = 4
	H = np.matrix([1, 0])
	G = np.matrix([deltaT * deltaT, deltaT / 2]).T
	X = np.linalg.matrix_power(G * G.T, x)
	Z = S_z * S_z
	F = np.matrix([[1, deltaT], [0, 1]])
	K = ((F * sigma * F.T) + X) * H.T * np.linalg.inv(H * ((F * sigma * F.T) + X) * H.T + Z)
	NextSigma = (np.identity(2) - (K * H)) * ((F * sigma * F.T) + X)
	Next_u = F * u + K * (z - H * F * u)
	return [Next_u, NextSigma]

def door_update(u, sigma, d, door_dist):
	door = 0.6
	no_door = 0.8
	index = int(u[0] / 100)
	if(index > 9):
		index = 9
	elif(index < 0):
		index = 0
	S = (door * door_dist[index]) + (1-no_door)*(1-door_dist[index])
	if d is True:
		door_dist[index] =  (door_dist[index] * door) / S
	else:
		door_dist[index]  = 1-(no_door)*(1-door_dist[index])/(1-S)
	return door_dist
