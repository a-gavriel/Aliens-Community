#define CONFIG_PATH "../misc/configFiles/"

#define FILE_NAME_BRIDGE_I "bridge_config_file_I.json"
#define FILE_NAME_BRIDGE_D "bridge_config_file_D.json"
#define FILE_NAME_BRIDGE_C "bridge_config_file_C.json"
#define FILE_NAME_ALIEN_N "alien_normal_config_file.json"
#define FILE_NAME_ALIEN_B "alien_beta_config_file.json"
#define FILE_NAME_ALIEN_GENERATOR "aliens_generator_config_file.json"

#define ALGORITHM_Y 0
#define ALGORITHM_SEM 1
#define ALGORITHM_SUR 2

#define SCHEDULER_RR 0          /*Round Robin*/
#define SCHEDULER_PRIOR 1       /*Priority*/
#define SCHEDULER_SJF 3         /*Shortes Job First*/
#define SCHEDULER_FIFO 4         /*First in First Out*/
#define SCHEDULER_LOTTERY 5         /*Lottery*/

typedef struct bridge
{
    int size;
    int max_weigth;
    int bridge_type;
    int scheduler_type;
    int queue_size;

} bridge_t;

typedef struct alien_normal
{
    int speed;      /*micro seconds*/

} alien_normal_t;

typedef struct alien_beta
{
    int execution_time;     /*micro seconds*/

} alien_beta_t;

typedef struct aliens_generator
{
    int normal;     /*Percentage*/
    int beta;       /*Percentage*/
    int alfa;       /*Percentage*/
    int mean;       /*micro seconds*/

} aliens_generator_t;

int Read_bridge_configFile(char *file_name, bridge_t *bridge);
int Read_alien_normal_configFile(char *file_name, alien_normal_t *alien);
int Read_alien_beta_configFile(char *file_name, alien_beta_t *alien);
int Read_aliens_generator_configFile(char *file_name, aliens_generator_t *generator);