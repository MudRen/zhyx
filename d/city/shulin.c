//By rama@lxtx

#include <room.h>
#include <ansi.h>

inherit ROOM;

void create()
{ 
        set("short", HIG"����"NOR);
        set("long",@LONG
��Ȼ��ɫһת��ǰ������һƬ��������֡��㿴���˿����ܣ�
������Χ��Щ�ط���̫��ͷ������ȴ˵�ϲ����������������ƺ���
Щ�������������׸���ô���أ��㲻�ɳ��������
LONG );
        set("outdoors", "yangzhou");
        set("exits", ([
                "east" :  __FILE__,
                "west" :  __FILE__,
                "south" : __FILE__,
                "north" : __FILE__,
        ])); 
/*        set("objects", ([   
             __DIR__"npc/xdh-guard" : 2,   
            ]));
            */   
        setup();            
}


int valid_leave(object me, string dir)
{
        int total_steps;

        if (me->query("bang_bad/name")=="С����")
        {
                total_steps = 1; 
        } else
                       
                total_steps = 20;
        
        if (dir == "north")
                me->add_temp("shulin/steps",1);

        if (dir == "south")
                me->add_temp("shulin/steps",-1);

        if (me->query_temp("shulin/steps") == total_steps)
        {
                me->move("/d/city/xdhzb");
                me->delete_temp("shulin/steps");
                write("�����ڵ���С���ᡣ\n");
                return -1;
        }  

        if (me->query_temp("shulin/steps") == - total_steps)
        {  
                me->move(__DIR__"shulin1");
                me->delete_temp("shulin/steps");
                write("�����˰����ֻص���ԭ�ء�\n");
                return -1;
        }

        return ::valid_leave(me,dir);
}
