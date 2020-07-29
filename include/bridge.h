typedef struct bridge_params
{
    int count;  /*Number of aliens inside the bridge*/
    int dir;    /*0 = Up to Botton, 1 = Botton to Up*/
    int max_weight;
    int pos;        /*0 = Left, 1 = Center, 2 = Right*/
    int type;       /*0 = Algorithm Y, 1 = Algorithm Sem, 2 = Algorithm Survival*/
} bridge_params_t;

bridge_params_t left_bridge;
bridge_params_t right_bridge;
bridge_params_t center_bridge;

bridge_params_t* bridges_t[3];

void BridgeMovements();

void Survival(bridge_params_t *bridge);


const int bridge_pairs [2][3][2];

const int bridge_routes [3];

const int bridge_pos[2][5];
const int bridge_dirs [2];

void Survival_AUX(bridge_params_t *bridge);
void Move_aliens(bridge_params_t *bridge);
int Has_space_int(bridge_params_t *bridge, int alien_weight);