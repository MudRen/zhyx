// hy_hy02.c 
inherit ROOM; 
void create() 
     { 
     set("short", "��  ԰"); 
     set("long", @LONG 
�����Ǻ���ҵĻ�԰��һ�߽�������ͱ�������ľ�ɫ��ס�ˡ�
�󿴿��ҿ����������ĳ����ȣ�����������
LONG); 
     set("exits", ([ 
         "east"     : __DIR__"hy_hy01" ,  
         "west"     : __FILE__ ,
         "south"    : __DIR__"hy_hy03" ,
         "north"    : __FILE__ ,
     ])); 
     set("no_sleep_room", "1"); 
     setup(); 
     replace_program(ROOM); 
     }

