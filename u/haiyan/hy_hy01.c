// hy_hy01.c 
inherit ROOM; 
void create() 
     { 
     set("short", "��  ԰"); 
     set("long", @LONG 
�����Ǻ���ҵĻ�԰��һ�߽�������ͱ�������ľ�ɫ��ס�ˡ�
�󿴿��ҿ����������ĳ����ȣ�����������
LONG); 
     set("exits", ([ 
         "east"     : __DIR__"hy_hy02",  
         "west"     : __FILE__ ,
         "south"    : __FILE__ ,
         "north"    : __FILE__ ,
     ])); 
     set("no_sleep_room", "1"); 
     setup(); 
     replace_program(ROOM); 
     }

