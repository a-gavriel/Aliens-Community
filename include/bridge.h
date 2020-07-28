typedef struct bridge_params
{
    int count;  /*Number of aliens inside the bridge*/
    int dir;    /*0 = Up to Botton, 1 = Botton to Up*/
    int max_weight;
    int position;   /*0 = Center, 1 = Right, -1 = Left*/
    int type;       /*0 = Algorithm Y, 1 = Algorithm Sem, 2 = Algorithm Survival*/
} bridge_params_t;

bridge_params_t left_bridge;
bridge_params_t right_bridge;
bridge_params_t center_bridge;

void BridgeMovements();

void Survival(bridge_params_t *bridge);

void Survival_AUX_L(bridge_params_t *bridge);
void Survival_AUX_R(bridge_params_t *bridge);
void Survival_AUX_C(bridge_params_t *bridge);
void Move();
int Has_space(bridge_params_t *bridge, alien_t alien);
