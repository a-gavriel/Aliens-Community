#ifndef _GRAPH_POINTS_H_
#define _GRAPH_POINTS_H_

typedef struct Point { 
    float x; 
    float y; 
} Point;

const Point A_in [32] = {{100,220},{100,190},{100,160},{100,130},{100,100},{100,70},{100,40},{100,10},
{130,10},{160,10},{190,10},{220,10},{250,10},{280,10},{310,10},{340,10},{370,10},{400,10},{430,10},{460,10},
{490,10},{520,10},{550,10},{580,10},{610,10},{640,10},{670,10},{700,10},{700,40},{700,70},{700,100},{700,130}};

const Point A_out [24] = {{170,210},{170,180},{170,150},{170,120},{170,90},{170,60},{200,60},
{230,60},{260,60},{290,60},{320,60},{350,60},{380,60},{410,60},{440,60},{470,60},
{500,60},{530,60},{560,60},{590,60},{620,60},{650,60},{650,90},{650,120}};

const Point down_top_left [12] = {{615,115},{585,115},{555,115},{525,115},{495,115},{465,115},{465,145},{465,175},{465,205},{465,235},{465,265},{465,295}};

const Point down_top_center [5] = {{645,170},{645,200},{645,230},{645,260},{645,290}};

const Point down_top_right [12] = {{695,115},{725,115},{755,115},{785,115},{815,115},{845,115},{845,145},{845,175},{845,205},{845,235},{845,265},{845,295}};

const Point up_top_left [12] = {{670,140},{640,140},{610,140},{580,140},{550,140},{520,140},{490,140},{490,170},{490,200},{490,230},{490,260},{490,290}};

const Point up_top_center [5] = {{675,170},{675,200},{675,230},{675,260},{675,290}};

const Point up_top_right [11] = {{730,140},{760,140},{790,140},{820,140},{850,140},{880,140},{880,170},{880,200},{880,230},{880,260},{880,290}};

//const Point bridge_left [] = {{470,320},{470,350},{470,380},{470,410},{470,440}};

//const Point bridge_center [] = {{860,320},{860,350},{860,380},{860,410},{860,440}};

//const Point bridge_right [] = {{660,320},{660,350},{660,380},{660,410},{660,440}};

const Point down_bottom_left [9] = {{460,470},{460,500},{460,530},{460,560},{460,590},{490,590},{520,590},{550,590},{580,590}};

const Point down_bottom_center [4] = {{645,470},{645,500},{645,530},{645,560}};

const Point down_bottom_right [11] = {{840,470},{840,500},{840,530},{840,560},{840,590},{810,590},{780,590},{750,590},{720,590},{690,590},{660,590}};

const Point up_bottom_left [9] = {{480,485},{480,515},{480,545},{480,575},{510,575},{540,575},{570,575},{600,575},{630,575}};

const Point up_bottom_center [4] = {{675,470},{675,500},{675,530},{675,560}};

const Point up_bottom_right [10] = {{870,485},{870,515},{870,545},{870,575},{870,605},{840,605},{810,605},{780,605},{750,605},{720,605}};

const Point B_in [32] = {{620,590},{620,620},{620,650},{620,680},{620,710},{650,710},{680,710},{710,710},{740,710},{770,710},{800,710},
{830,710},{860,710},{890,710},{920,710},{950,710},{980,710},{1010,710},{1040,710},{1070,710},{1100,710},{1130,710},{1160,710},
{1190,710},{1220,710},{1220,680},{1220,650},{1220,620},{1220,590},{1220,560},{1220,530},{1220,500}};

const Point B_out [23] = {{675,600},{675,630},{675,660},{705,660},{735,660},{765,660},{795,660},{825,660},{855,660},
{885,660},{915,660},{945,660},{975,660},{1005,660},{1035,660},{1065,660},{1095,660},{1125,660},{1125,630},
{1125,600},{1125,570},{1125,540},{1125,510}};

const int routes_sizes[16] = {32,24,12,5,12,12,5,11,9,4,11,9,4,10,32,23};

const Point *routes_coords[16] = {A_in, A_out, down_top_left, down_top_center, 
down_top_right, up_top_left, up_top_center, up_top_right, 
down_bottom_left, down_bottom_center, down_bottom_right, 
up_bottom_left, up_bottom_center, up_bottom_right, B_in, B_out};



#endif