inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "��ԭ");
        set("long",
"�����Ѿ������ӽ��ɹž�Ӫ�ˣ�����е��˴�����ǰ��Ȼ������������
����ȥ���Ĵ�����ãã��ݺ������˲���������һ����������׳�ĸо���\n"
);
        set("outdoors", "xiangyang");
        set("no_magic",1);

        set("exits", ([
                "east"  : __DIR__"shanlu3",
                "west"  : __DIR__"shanlu3",
        ]));

        setup();
}

void init()
{
        object me=this_player();

        me->start_busy(random(2));


        if( me->query_temp("yidao/mark_steps") > 11 )
        {
         me->move(__DIR__"caoyuan");
         me->delete_temp("yidao");
         tell_object(me,YEL"һ·�糾����֮���ɹŴ��ԭ�Ѿ�������ǰ��......\n"NOR);
         return;
        } 

        if( me->query_temp("yidao/mark_steps") < -11 )
        {
         me->move(__DIR__"dhunya");
         me->delete_temp("yidao");
         tell_object(me,YEL"һ·�糾����֮�󣬶ϻ����Ѿ�������ǰ��......\n"NOR); 
         return;
        }
        tell_object(me,HIG"��ָ���Ŵ�����н���ãã�Ĳ�ԭ��......\n"NOR);  
}

int valid_leave(object me,string dir)
{
       if( dir == "west" )
       me->add_temp("yidao/mark_steps",-random(2));
       if(  dir == "east" )
       me->add_temp("yidao/mark_steps",random(2));
       return ::valid_leave(me,dir);
}

