'''
Pedram Safaei
Project [3]
CS 482
Bugs: There are some weird bugs with the grapgical environment but 
I do not know how to reproduce it and it only happens once or twice 
after testing it for more than 10 times
'''
#!/usr/bin/python
import argparse
import logging
import sys
import numpy as np
import gym
#import gym.scoreboard.scoring
from gym import wrappers, logger
################################################
# CS482: this is the function that changes the
# continuous values of the state of the cart-
# pole into a single integer state value, you'll
# have to adjust this for the mountain car task
################################################
def discretize_state(x, x_prime):
    zero = 0.9
    one = 0.7
    two = 0.5
    three = 0.3
    four = 0.1
    five = 0.075
    six = 0.2
    seven = 0.5
    box = 0
    if x < -1.2 or x > 0.6:
        return -1
    if x < -zero:
        box = 0
    elif x < -one:
        box = 1
    elif x < -two:
        box = 2
    elif x < -three:
        box = 3
    elif x < -four:
        box = 4
    elif x < five:
        box = 5
    elif x < six:
        box = 6
    elif x < seven:
        box = 7
    else:
        box = 8
    box *= 9
    dot_zero = 0.05
    dot_one = 0.025
    if x_prime < -dot_zero:
        box += 0
    elif x_prime < -dot_one:
        box += 1
    elif x_prime < 0.0:
        box += 2
    elif x_prime < dot_one:
        box += 3
    elif x_prime < dot_zero:
        box += 4
    else:
        box += 5
    return box
if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=None)
    ############################################
    # CS482: This is the line you'll have to
    # change to switch to the mountain car task
    ############################################
    parser.add_argument('env_id', nargs='?', default='MountainCar-v0', help='Select the environment to run')
    args = parser.parse_args()
    logger = logging.getLogger()
    formatter = logging.Formatter('[%(asctime)s] %(message)s')
    handler = logging.StreamHandler(sys.stderr)
    handler.setFormatter(formatter)
    logger.addHandler(handler)
    # You can set the level to logging.DEBUG or logging.WARN if you
    # want to change the amount of output.
    logger.setLevel(logging.INFO)
    env = gym.make(args.env_id)
    outdir = '/tmp/' + 'qagent' + '-results'
    env = wrappers.Monitor(env, outdir, write_upon_reset=True, force=True)
    env.seed(0)
    ############################################
    # CS482: This initial Q-table size should 
    # change to fit the number of actions (columns)
    # and the number of observations (rows)
    ############################################
    Q = np.zeros([78, env.action_space.n])
    ############################################
    # CS482: Here are some of the RL parameters
    # you can adjust to change the learning rate
    # (alpha) and the discount factor (gamma)
    ############################################
    alpha = 0.3 
    gamma = 0.8 
    n_episodes = 50001
    for episode in range(n_episodes):
        tick = 0
        reward = 0
        done = False
        state = env.reset()
        s = discretize_state(state[0], state[1])
        while done != True:
            tick += 1
            action = 0
            ri = -999
            for q in range(env.action_space.n):
                if Q[s][q] > ri:
                    action = q
                    ri = Q[s][q]
            state, reward, done, info = env.step(action)
            sprime = discretize_state(state[0], state[1])
            predicted_value = np.max(Q[sprime])
            if sprime < 0:
                predicted_value = 0
                reward = -5
            Q[s,action] += alpha * ((reward + (gamma * predicted_value)) - (Q[s,action]))
            s = sprime
        if episode % 1000 == 0:
            alpha *= .996
        ############################################
        # CS482: When switching to the mountain car
        # task, you will have to change this to
        # reflect the success/failure of the mountain
        # car task
        ############################################
        #print state[0]
        #print s 
        #print x
        print ("Episode: ", episode)
        if state[0] < 0.5:
            print ("NO NO NO (Fail!) | state: ", state[0] )
        else: 
            print ("YES YES YES (Pass!) | state: ", state[0])