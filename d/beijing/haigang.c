#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "����֮��");
        set("long", @LONG
������Ǵ�֮�����˻��Ĵ��Ž�ʯ����������������������һȺȺ��
Ÿ��ŷŷ..���ؽ��ţ���ʱ�����Ծ�����棬��������˻����������Ҵ�
��(chuan)�� �������ż����������ˣ��˴��ɶɹ��󺣵��ﺣ����һ�ˡ�
����һֱ�߾����ྩ�ˣ�������һ���޼ʵĴ󺣡���Ŀ���������������ؿ�
���������⳩����ȷ��һ���þӴ���
LONG );
        set("exits", ([
                "west" : __DIR__"road10",
                "north" : "/d/tulong/tulong/haian",
        ]));
        set("item_desc", ([
                "chuan" : "һ�Ҵ󷫴�����úܽ�ʵ���������Գ�Զ���ġ�\n",
        ]));
        set("objects", ([
                "/d/shenlong/npc/chuanfu" :1,
        ]));
        set("max_room", 3);
        set("outdoors", "beijing");
        set("navigate",1);
        set("opposite","/d/shenlong/haitan");
        setup();
}
void init()
{
        object dao, room, ren, ding;
        object me = this_player();
        room = load_object("/d/tulong/tulong/huichang");
        ding = present("chang jinpeng", room);

        if (objectp(ding)) 
        dao = present("tulong blade", ding);

        if (objectp(dao))
        {
                room = load_object("/d/tulong/tulong/daobian");
                ren = present("bai guishou",room);
                message_vision(HIC "�㿴��������ͣ�����˺��������еĺ���ȫ���������Ӯ�̵ı�ǡ�\n"NOR, me);
                message_vision(CYN "�׹��ٶ���˵��������ӥ�̵õ�������������λ����ͬ����Ը��μ��ﵶ������᣿\n"NOR, me);
                shout(HIR "\n������������" NOR+WHT "�׹�������һ����Ц��" NOR );
                shout(HIR "\n������������" NOR+WHT "�׹��٣�����ӥ�̵õ�������������������ɽ�������ﵶ������ᡣ\n" NOR );
                remove_call_out("mes");
                call_out("mes",3,this_player());
                this_player()->set_temp("to_wang",1);
                add_action("do_accept","accept");
        }
}

void mes(object me)
{
        message_vision(HIR "��Ը��μ�(accept)����ɽ���ﵶ���������\n"NOR, me);
}

int do_accept()
{
        object me = this_player();
        if (me->query_temp("to_wang")) 
        {
                tell_object(me, HIR "�����ȥ�μ��ﵶ������ᡣ\n" NOR);
                remove_call_out("moveto");
                call_out("moveto",10,me);
        }
        return 1;
}

int moveto(object me)
{
        me->move("/d/tulong/tulong/boat");
        message_vision(HIC "\n$N��������ӥ�̵Ĵ󴬣����������ֺ������������ˣ����������������ʻ����\n"NOR, me);
        remove_call_out("arrive1");
        call_out("arrive1",10,me);
        return 1;
}

int arrive1(object me)
{
        message_vision(HIB "\n��ӥ�̵Ĵ��ڴ���������Ư��......$N�����е�˯�����ʡ�\n"NOR, me);
        remove_call_out("arrive2");
        call_out("arrive2",10,me);
        return 1;
}

int arrive2(object me)
{
        message_vision(HIY "\n$NͻȻ����һ�����ȣ������ˣ��´��ɡ���$N��ʱ�����񣬸�����ӥ�̽������˴���\n"NOR, me);
        me->move("/d/tulong/tulong/daobian");
        tell_object(me, HIR "\n��ͻȻ�뵽����������������˵Ĵ�(break boat)����������·���ӡ�\n" NOR);
        return 1;
}


