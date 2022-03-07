/**
 * 
 * Reference: http://manpages.ubuntu.com/manpages/bionic/man3/libmosquitto.3.html
 * 
 * compile with libmosquitto
 * install mosquitto broker, client and libmosquitto-dev
 * Run mosquitto deamon with below command 
 * $ mosquitto -d
 * Publish message to topics using mosquitto_pub
 * $ mosquitto_pub -d -t testTopic -m "message"
 * 
 * **/

#define TOPIC_NAME  "$SYS/#"
// #define TOPIC_NAME  "testTopic"

#include <stdio.h>
#include <mosquitto.h>

void my_message_callback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message)
{
    if(message->payloadlen){
       printf("%s %s\n", message->topic, (char*)message->payload);
    }else{
       printf("%s (null)\n", message->topic);
    }
    fflush(stdout);
}

void my_connect_callback(struct mosquitto *mosq, void *userdata, int result)
{
    int i;
    if(!result){
       /* Subscribe to broker information topics on successful connect. */
        mosquitto_subscribe(mosq, NULL, TOPIC_NAME, 2);
    }else{
       fprintf(stderr, "Connect failed\n");
    }
}

void my_subscribe_callback(struct mosquitto *mosq, void *userdata, int mid, int qos_count, const int *granted_qos)
{
    int i;

    printf("Subscribed (mid: %d): %d", mid, granted_qos[0]);
    for(i=1; i<qos_count; i++){
       printf(", %d", granted_qos[i]);
    }
    printf("\n");
}

void my_log_callback(struct mosquitto *mosq, void *userdata, int level, const char *str)
{
    /* Pring all log messages regardless of level. */
    printf("%s\n", str);
}

int main(int argc, char *argv[])
{
    int i;
    char *host = "localhost";
    int port = 1883;
    int keepalive = 60;
    bool clean_session = true;
    struct mosquitto *mosq = NULL;

    mosquitto_lib_init();
    mosq = mosquitto_new(NULL, clean_session, NULL);
    if(!mosq){
       fprintf(stderr, "Error: Out of memory.\n");
       return 1;
    }
    mosquitto_log_callback_set(mosq, my_log_callback);
    mosquitto_connect_callback_set(mosq, my_connect_callback);
    mosquitto_message_callback_set(mosq, my_message_callback);
    mosquitto_subscribe_callback_set(mosq, my_subscribe_callback);

    if(mosquitto_connect(mosq, host, port, keepalive)){
       fprintf(stderr, "Unable to connect.\n");
       return 1;
    }

    mosquitto_loop_forever(mosq, -1, 1);

    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
    return 0;
}