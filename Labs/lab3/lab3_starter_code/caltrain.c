#include "caltrain.h"

#define VERBOSE 0 // dummy variable for debugging

void station_init(struct station *station) {
    station->waiting_passengers = 0;
    station->free_seats = 0;
    station->seated_passengers =0;
    pthread_mutex_init(&(station->Mutex_door), NULL);
    pthread_cond_init(&(station->Cond_train_arrived), NULL);
    pthread_cond_init(&(station->Cond_passengers_seated), NULL);
}

void station_load_train(struct station *station, int count) {

    pthread_mutex_lock(&(station->Mutex_door));

    station->free_seats = count;
    station->seated_passengers = count;

    if(VERBOSE){
        printf("=================NEW TRAIN ARRIVAL=================\n");
        printf("UPDATE:\n");
        printf("THE TRAIN HAS (%d) EMPTY SEATS\n", station->free_seats);
        printf("THE STATION HAS (%d) WAITING PASSENGERS\n", station->waiting_passengers);
    }

    // no passengers waiting
    // train leaves
    if (station->waiting_passengers == 0) {
        if(VERBOSE){
            printf("UPDATE:\n");
            printf("THERE IS NO PASSENGERS HERE\n");
        }
        pthread_mutex_unlock(&(station->Mutex_door));
        if(VERBOSE){
            printf("UPDATE:\n");
            printf("THE TRAIN IS MOVING\n");
        }
        // setting seats to zero as the train is moving
        // this line is important to avoid the case of the previous train had seats but there was no passengers to sit in 
        station->free_seats = 0;
        return;
    }

    // train arrived with no seates
    // train leaves
    else if (station->free_seats == 0) 
    {
        if(VERBOSE){
            printf("UPDATE:\n");
            printf("THERE IS NO SEATS HERE\n");
        }
        pthread_mutex_unlock(&(station->Mutex_door));
        if(VERBOSE){
            printf("UPDATE:\n");
            printf("THE TRAIN IS MOVING\n");
        }
        station->free_seats = 0;
        return;
    }

    else{
    // conditions for waiting:
    // there is a number of seats empty
    // there is passengers to enter the tarin
    // there is standing passengers to sit 
    while(!((station->free_seats == 0) || (station->waiting_passengers == 0) || (station-> seated_passengers == 0)))
    {   

        if(VERBOSE){
            printf("UPDATE:\n");
            printf("TRAIN IS WAITING FOR PASSENGERS\n");
        }
        
        // There are passengers waiting
        pthread_cond_broadcast(&(station->Cond_train_arrived));
        // Wait until all passengers are seated
        pthread_cond_wait(&(station->Cond_passengers_seated), &(station->Mutex_door));
        
        if(VERBOSE){
            printf("UPDATE:\n");
            printf("TRAIN IS WAITING FOR PASSENGERS TO SIT\n");
        }
        
        pthread_mutex_unlock(&(station->Mutex_door));
        if(VERBOSE){
            printf("UPDATE:\n");
            printf("THE TRAIN IS MOVING\n");
        }
        station->free_seats = 0;
        return;
    }

    pthread_mutex_unlock(&(station->Mutex_door));
    if(VERBOSE){
        printf("UPDATE:\n");
        printf("TRAIN IS WAITING FOR PASSENGERS TO SIT\n");
    }
    station->free_seats = 0;
    if(VERBOSE){
            printf("UPDATE:\n");
            printf("THE TRAIN IS MOVING\n");
        }
    return;
    }
}

void station_wait_for_train(struct station *station) {

    pthread_mutex_lock(&(station->Mutex_door));
    station->waiting_passengers++;
    if(VERBOSE){
        printf("UPDATE:\n");
        printf("PASSENGER WAITING NUMBER IS========>(%d)\n", station->waiting_passengers);
    }
    
    while((station->free_seats < 1))
    {
        pthread_cond_wait(&(station->Cond_train_arrived), &(station->Mutex_door));
    }
    // Wait until a train is in the station and there are enough free seats
    if ((station->free_seats >= 1)) // dont wait if there is only one char at least
    {
    station->free_seats--;
        
    if(VERBOSE){
        printf("UPDATE:\n");
        printf("NUMBER OF EMPTY SEATS-------------->(%d)\n", station->free_seats);
    }
    pthread_mutex_unlock(&(station->Mutex_door));
    }
}

void station_on_board(struct station *station) {
    station->waiting_passengers--;
    station->seated_passengers--;

    if(VERBOSE){
        printf("UPDATE:\n");
        printf("PASSENGER ENTERED NUMBER IS========>(%d)\n", station->waiting_passengers + 1);
    }

    pthread_mutex_lock(&(station->Mutex_door));
    // A seat becomes available, so a passenger can board
    if(VERBOSE){
        printf("UPDATE:\n");
        printf("A PASSENGER IS SEATED\n");
        printf("LEFT PASSENGER TO BE SEATED IS +++>(%d)\n", station->seated_passengers);
    }

    // If all the free seats are filled, signal the train to leave
    if ((station->seated_passengers == 0)  || (station->waiting_passengers == 0))
	{
        if(VERBOSE){
        	printf("UPDATE:\n");
	    	printf("THE TRAIN WILL BE LAUCHED NO MORE SEATS\n");
        }
        pthread_cond_signal(&(station->Cond_passengers_seated));
    }

    pthread_mutex_unlock(&(station->Mutex_door));
}