
#define PLACE_FILE  "/u/sanben/xquest/dbase/place" //定义地名数据库文件路径
#define NPC_FILE    "/u/sanben/xquest/dbase/npc"  //定义NPC数据库文件路径
#define ITEM_FILE    "/u/sanben/xquest/dbase/item"//定义购买物品数据库文件路径
#define RIDDLE_FILE  "/u/sanben/xquest/dbase/riddle"//定义谜语数据库文件路径

string set_place()
{
         string file, *lines, where;

         file = read_file(PLACE_FILE);
         lines = explode(file, "\n");
         where = lines[random(sizeof(lines))];

         return where;

}

string set_npc()
{
         string file, *lines, npc;

         file = read_file(NPC_FILE);
         lines = explode(file, "\n");
         npc = lines[random(sizeof(lines))];

         return npc;

 }

string set_item()
{
         string file, *lines, item;

         file = read_file(ITEM_FILE);
         lines = explode(file, "\n");
         item = lines[random(sizeof(lines))];

         return item;

 }

 string set_riddle()
{
         string file, *lines, riddle;

         file = read_file(RIDDLE_FILE);
         lines = explode(file, "\n");
         riddle = lines[random(sizeof(lines))];

         return riddle;

}
