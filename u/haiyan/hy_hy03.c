// hy_hy03.c 
inherit ROOM; 
void create() 
     { 
     set("short", "��  ԰"); 
     set("long", @LONG 
�����Ǻ���ҵĻ�԰��һ�߽�������ͱ�������ľ�ɫ��ס�ˡ�
�󿴿��ҿ����������ĳ����ȣ�����������
LONG); 
     set("exits", ([ 
         "east"     : __FILE__ ,  
         "west"     : __DIR__"hy_houting" ,
         "south"    : __DIR__"hy_hy02" ,
         "north"    : __DIR__"hy_hy01" ,
     ])); 
     set("no_sleep_room", "1"); 
     setup(); 
     replace_program(ROOM); 
     }

