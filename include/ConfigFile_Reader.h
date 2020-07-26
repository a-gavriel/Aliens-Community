#define CONFIG_PATH "../misc/configFiles/"

typedef struct bridge
{
    int size;
    int max_weigth;

} bridge_t;

int Read_bridge_configFile(char *file_name, bridge_t *bridge);