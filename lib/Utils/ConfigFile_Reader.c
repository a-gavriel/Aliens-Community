#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/json.h"
#include "../../include/ConfigFile_Reader.h"

int Read_bridge_configFile(char *file_name, bridge_t *bridge)
{
    FILE *fp;
	char buffer[1024];
    struct json_object *parsed_json;
	struct json_object *size;
	struct json_object *max_weigth;
    struct json_object *bridge_type;
    struct json_object *scheduler_type;
    struct json_object *queue_size;
	char *full_path = malloc(strlen(file_name) + strlen(CONFIG_PATH)+1);
    if(full_path == NULL)
    {
        return EXIT_FAILURE;
    }
    strcpy(full_path, CONFIG_PATH);
    strcat(full_path, file_name);
	fp = fopen(full_path,"r");

	fread(buffer, 1024, 1, fp);
	fclose(fp);

	parsed_json = json_tokener_parse(buffer);

	json_object_object_get_ex(parsed_json, "Size", &size);
	json_object_object_get_ex(parsed_json, "MaxWeight", &max_weigth);
    json_object_object_get_ex(parsed_json, "BridgeType", &bridge_type);
    json_object_object_get_ex(parsed_json, "SchedulerType", &scheduler_type);
    json_object_object_get_ex(parsed_json, "QueueSize", &queue_size);
    //printf("Name: %s\n", json_object_get_string(name));
    bridge->size = json_object_get_int(size);
    bridge->max_weigth = json_object_get_int(max_weigth);
    bridge->bridge_type = json_object_get_int(bridge_type);
    bridge->scheduler_type = json_object_get_int(scheduler_type);
    bridge->queue_size = json_object_get_int(queue_size);

	return EXIT_SUCCESS;
}

int Read_alien_normal_configFile(char *file_name, alien_normal_t *alien)
{
    FILE *fp;
	char buffer[1024];
    struct json_object *parsed_json;
	struct json_object *speed;

	char *full_path = malloc(strlen(file_name) + strlen(CONFIG_PATH)+1);
    if(full_path == NULL)
    {
        return EXIT_FAILURE;
    }
    strcpy(full_path, CONFIG_PATH);
    strcat(full_path, file_name);
	fp = fopen(full_path,"r");

	fread(buffer, 1024, 1, fp);
	fclose(fp);

	parsed_json = json_tokener_parse(buffer);

	json_object_object_get_ex(parsed_json, "Speed", &speed);
    //printf("Name: %s\n", json_object_get_string(name));
    alien->speed = json_object_get_int(speed);

	return EXIT_SUCCESS;
}

int Read_alien_beta_configFile(char *file_name, alien_beta_t *alien)
{
    FILE *fp;
	char buffer[1024];
    struct json_object *parsed_json;
	struct json_object *time;

	char *full_path = malloc(strlen(file_name) + strlen(CONFIG_PATH)+1);
    if(full_path == NULL)
    {
        return EXIT_FAILURE;
    }
    strcpy(full_path, CONFIG_PATH);
    strcat(full_path, file_name);
	fp = fopen(full_path,"r");

	fread(buffer, 1024, 1, fp);
	fclose(fp);

	parsed_json = json_tokener_parse(buffer);

	json_object_object_get_ex(parsed_json, "Time", &time);
    //printf("Name: %s\n", json_object_get_string(name));
    alien->execution_time = json_object_get_int(time);

	return EXIT_SUCCESS;
}

int Read_aliens_generator_configFile(char *file_name, aliens_generator_t *generator)
{
    FILE *fp;
	char buffer[1024];
    struct json_object *parsed_json;
	struct json_object *normal;
	struct json_object *beta;
    struct json_object *alfa;
    struct json_object *mean;
	char *full_path = malloc(strlen(file_name) + strlen(CONFIG_PATH)+1);
    if(full_path == NULL)
    {
        return EXIT_FAILURE;
    }
    strcpy(full_path, CONFIG_PATH);
    strcat(full_path, file_name);
	fp = fopen(full_path,"r");

	fread(buffer, 1024, 1, fp);
	fclose(fp);

	parsed_json = json_tokener_parse(buffer);

	json_object_object_get_ex(parsed_json, "Normal", &normal);
	json_object_object_get_ex(parsed_json, "Beta", &beta);
    json_object_object_get_ex(parsed_json, "Alfa", &alfa);
    json_object_object_get_ex(parsed_json, "Mean", &mean);
    //printf("Name: %s\n", json_object_get_string(name));
    generator->normal = json_object_get_int(normal);
    generator->beta = json_object_get_int(beta);
    generator->alfa = json_object_get_int(alfa);
    generator->mean = json_object_get_int(mean);
    return EXIT_SUCCESS;
}