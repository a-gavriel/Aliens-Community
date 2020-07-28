typedef struct bridge_params
{
    int count;  /*Number of aliens inside the bridge*/
    int dir;    /*0 = Up to Botton, 1 = Botton to Up*/
    int max_weight;
    int type;   /*0 = Center, 1 = Right, -1 = Left*/
} bridge_params_t;

void Survival(bridge_params_t *bridge);