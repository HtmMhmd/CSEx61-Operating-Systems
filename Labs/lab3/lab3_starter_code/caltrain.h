/**
 * @file caltrain.h
 * @author hatem mohamed ()
 * @brief 
 * @version 
 * @date 2024-03-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>



#ifndef CALTRAIN_H
#define CALTRAIN_H

#ifndef NULL
#define NULL 0
#endif
/*============================================================================*/
/*===========================TYPES DEFINATIONS================================*/
/*============================================================================*/

/**
 * @brief 
 * 
 */
// Define the station structure
struct station {
    int waiting_passengers; // passengers waiting at the station
    int free_seats; // free seats in the train
    int seated_passengers; // seated passengers after enterng the train
    int entered;
    pthread_mutex_t Mutex_door; // mutex lock
    pthread_cond_t Cond_train_arrived; // condition variable for train arrival
    pthread_cond_t Cond_passengers_seated; // condition variable for passengers seated
};

/*============================================================================*/
/*=======================FUNCTIONS DEFINATIONS================================*/
/*============================================================================*/

/**
 * @brief 
 * 
 * @param station 
 */
void station_init(struct station *station);
/**
 * @brief When a train arrives in the station and has opened its doors, it invokes the function. 
 * The function should not return until all passengers are seated and the train is either full or all waiting passengers have boarded.
 * 
 * @param station 
 * @param count : indicates the number of available seats on the train.
 */
void station_load_train(struct station *station, int count);
/**
 * @brief 
 * SIMULATION : a button the passenger clicks when he enters and leave it when he exits.
 * This function is called when a passenger robot arrives at the station.
 * It should not return until a train is in the station with enough free seats for the passenger.
 * Once the function returns, the passenger robot will board the train
 * 
 * @param station 
 */
void station_wait_for_train(struct station *station);
/**
 * @brief This function is called once a passenger is seated.
 * It signals the train that the passenger is on board.
 * 
 * 
 * @param station 
 */
void station_on_board(struct station *station);

#endif