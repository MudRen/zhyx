#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW "\n\n      ̫        ��        ��        ��\n" NOR);
        set("long", WHT "\n"
"��ãã��һƬ���ֲ������������ǵأ���ΧһƬ�ž���\n"
"����Ǵ�˵�е�̫��þ���\n" NOR);
 set("exits", ([ 
            "chushengdao"   : "/d/special/liudaolunhui/chushengdao",   
            "diyudao"   : "/d/special/liudaolunhui/diyudao",   
            "eguidao"   : "/d/special/liudaolunhui/eguidao",  
            "rendao"   : "/d/special/liudaolunhui/rendao",     	  
            "tiandao"   : "/d/special/liudaolunhui/tiandao",   
            "xiuluodao"   : "/d/special/liudaolunhui/xiuluodao",     	 
        ]));
        setup();
}

