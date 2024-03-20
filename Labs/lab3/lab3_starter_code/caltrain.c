#include "caltrain.h"

void station_init(struct station *station) {
    station-> entered = 0;

    station->waiting_passengers = 0;

    station->free_seats = 0;

    station->seated_passengers =0;

    pthread_mutex_init(&(station->Mutex_door), NULL);

    pthread_cond_init(&(station->Cond_train_arrived), NULL);

    pthread_cond_init(&(station->Cond_passengers_seated), NULL);
}

void station_load_train(struct station *station, int count) {

    station->free_seats = count;
    
    station->seated_passengers = -1 * count;

    printf("UPDATE:\n");
    printf("THE TRAIN HAS (%d) EMPTY SEATS\n", station->free_seats);
    // train arrived with no seates
    if (station->free_seats == 0) 
    {
        printf("UPDATE:\n");
        printf("THERE IS NO SEATS HERE\n");
        return;
    }
    // no passengers waiting

    else if (station->waiting_passengers == 0) {
        printf("UPDATE:\n");
        printf("THERE IS NO PASSENGERS HERE\n");
        return;
    }

    while((station->free_seats > 0) || (station->waiting_passengers > 0) || (station->seated_passengers < 0))
    {
        pthread_mutex_lock(&(station->Mutex_door));
        // There are passengers waiting
        pthread_cond_broadcast(&(station->Cond_train_arrived));

        // Wait until all passengers are seated
        pthread_cond_wait(&(station->Cond_passengers_seated), &(station->Mutex_door));

        pthread_mutex_unlock(&(station->Mutex_door));
        return;
    }
    return;
}

void station_wait_for_train(struct station *station) {
    pthread_mutex_lock(&(station->Mutex_door));
    station->waiting_passengers++;

    printf("UPDATE:\n");
    printf("PASSENGER WAITING NUMBER IS========>(%d)\n", station->waiting_passengers);

    // Wait until a train is in the station and there are enough free seats
    while ((station->free_seats <1)) // dont wait if there is only one char at least
    {
        pthread_cond_wait(&(station->Cond_train_arrived), &(station->Mutex_door));
    }
    station->waiting_passengers--;
    station->free_seats--;
    printf("UPDATE:\n");
    printf("A PASSENGER ENTERED _______________>(%d)\n",++station->entered);
    printf("PASSENGER ENTERED NUMBER IS========>(%d)\n", station->waiting_passengers + 1);
    printf("NUMBER OF EMPTY SEATS-------------->(%d)\n", station->free_seats);

    pthread_mutex_unlock(&(station->Mutex_door));
}

void station_on_board(struct station *station) {

    station->seated_passengers++;

    pthread_mutex_lock(&(station->Mutex_door));
    // A seat becomes available, so a passenger can board

    printf("UPDATE:\n");
    printf("A PASSENGER IS SEATED\n");
    printf("LEFT PASSENGER TO BE SEATED IS +++>(%d)\n", station->seated_passengers);


    // If all the free seats are filled, signal the train to leave
    if ((station->seated_passengers == 0)) 
	{
		printf("UPDATE:\n");
		printf("THE TRAIN WILL BE LAUCHED NO MORE SEATS\n");
        pthread_cond_signal(&(station->Cond_passengers_seated));
    }

    pthread_mutex_unlock(&(station->Mutex_door));
}