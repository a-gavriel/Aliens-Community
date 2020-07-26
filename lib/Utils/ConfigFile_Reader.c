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

    //printf("Name: %s\n", json_object_get_string(name));
    bridge->size = json_object_get_int(size);
    bridge->max_weigth = json_object_get_int(max_weigth);
	return EXIT_SUCCESS;
}