// Code of ShenZhou
#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
	object ob;

        set("short", "ʯ������");
        set("long", @LONG
�����һ���ʯ���������ڵأ��ı�(wall)�ϻ��Ŷ�ʮ������ͼ������
�����������������󡣵���һ��̫��ͼ(tu)����Χ�ֱ������������
������ԣ���Ȧ�������ݶ�������ʮ���ԡ�һ�������Ȼע�£�ӳ������
�����������ƺ�������ţ����ƺ������ӳ£�����֮�䣬������ĥ��
LONG
        );

        set("exits", ([
                "up" : "/d/taohua/neidong",
        ]));

        set("no_fight", 1);
	set("no_steal", 1);
	set("no_beg",1);

        set("item_desc", ([
                "tu" : "̫��ͼ����(yin)������(yang)��������ҡ�\n",
		"wall" :
"�������ޣ���ľ�ԡ���������ص���ѡ����º��������á�β�𻢡���ˮ��\n"
"�׻����ޣ���ľ�ǡ�¦�𹷡�θ���������ռ���������������ˮԳ\n"
"��ȸ���ޣ���ľ�����������⯡�����������¹����ˮ�ߡ������\n"
"�������ޣ���ľⳡ�ţ����Ů����������Σ���ࡢ�һ�����ˮ�����᣾\n",
        ]));

	set("cost", 1);

        setup();
}

void init()
{
        add_action("do_sit", "sit");
	add_action("do_stand", "stand");
	add_action("do_leave", "leave");
	add_action("do_think", "lingwu");
}

int do_think()
{
	object me = this_player();
	int qmwx = me->query_skill("qimen-wuxing",1);

	if (me->is_busy())
		return notify_fail("��������æ���ء�\n");

	if (!me->query_temp("sitted") && !me->query_temp("standed") )
		return notify_fail("�㿴�ŵ��ϵ�̫��ͼ����ĥ���Ƿ������(sit)��ȥ����վ(stand)��ȥ��\n");

	if( !query("yin") || !query("yang") )
		return notify_fail("̫��ͼ��ֻ����һ���ˣ��㻹��Ҫһλͬ��Э���˹���\n");

	if ( me->query_skill("qimen-wuxing", 1) < 170 &&
	  !present("he tu", me) && !present("luo shu", me) ) 
	{
		tell_object(me,MAG"��ֻ����Ѫ��ӿ�����������������Ϯ����\n"NOR);
		me->unconcious();
		return 1;
	}

	if( !me->query("taohua_maze") ) {
		tell_object(me,MAG"��ֻ����Ѫ��ӿ�����������������Ϯ����\n"NOR);
		me->unconcious();
		return 1;
	}

	if( me->query("jing") < 100 )
		return notify_fail("�����ھ��񲻼ѣ��޷���������˼����\n");

	if( (int)me->query("potential") - (int)me->query("learned_points") < 1 )
		return notify_fail("���Ǳ�ܲ��㣬�޷���������书��\n");

	me->receive_damage("jing", random(qmwx));

	if(random(20) == 0) {
		me->add("potential", -2);
		me->improve_skill("qimen-wuxing", qmwx/2 + random(qmwx*2));
		write( "ֻ�����л�Ȼ���ʣ�����������е������ֽ���һ�㣡\n" );
	}
	else if(random(10) == 0) {
		me->add("potential", -1);
		me->improve_skill("qimen-wuxing", qmwx/5 + random(qmwx*2));
		write( "��ڤ˼���룬���������н�������һ����ᣡ\n" );
	}
        else if(random(2) == 0) {
                me->improve_skill("qimen-wuxing", qmwx/10 + random(qmwx/2));
                write( "����˼������Լ���յ�����������֮�е�һЩ�ѽ�֮����\n" );
        }
	else {
                write( "������������Ǳ�Ŀ�˼���������ϵ��ѽ�֮����\n" ); 
	}
	return 1;
}

int do_sit(string arg)
{
        mapping skl;
        object me=this_player();
        string *sname;
        int i,j;

        if( !arg ) 
		return notify_fail("�����������\n");

	if( arg != "yin")
		return notify_fail("�����صأ���Ҫ���������\n");


	if( !me->query("family") || me->query("family/family_name") != "�һ���")
		return notify_fail("�㱿׾���������������ϣ����һ������������ƨ�ɣ���һ��������������\n");

	if( me->query_temp("sitted"))
		return notify_fail("���Ѿ����ڡ����������ˣ�\n");

        if( me->query_temp("standed"))
                return notify_fail("���Ѿ�վ�ڡ����������ˣ�\n");

	if( query("yin")){
		write(query("yin")->name()+"�Ѿ����ڡ����������ˣ�\n");
		tell_object(query("yin"),"������"+me->query("name")+"Ҳ����������\n");
		return 1;
	}

	message_vision("$N��ϥ������������ͼ��\n", me);

	if ( me->query_skill("qimen-wuxing", 1) < 150 &&
	     !present("he tu", me) && !present("luo shu", me) )
	{
		tell_object(me,MAG"��ֻ����Ѫ��ӿ�����������������Ϯ����\n"NOR);
		me->unconcious();
		return 1;
	}

	message_vision(HIG"$N�۹۱ǣ��ǹ��ģ�������ֹ������ֹ�����֮�����������⡣\n"NOR, me);
	me->set_temp("sitted", 1);
	set("yin", me);

	return 1;
}

int do_stand(string arg)
{
	mapping skl;
	object me=this_player();
        string *sname;
        int i,j;

        if( !arg ) 
		return notify_fail("����վ�����\n");

	if( arg != "yang")
		return notify_fail("�����صأ���Ҫ�洦���ߣ�\n");

	if( !me->query("family") || me->query("family/family_name") != "�һ���")
		return notify_fail("�㱿׾����վ���������ϣ����һ����С�ģ�ˤ���Ľų��졣\n");

        if( me->query_temp("standed"))
                return notify_fail("���Ѿ�վ�ڡ����������ˣ�\n");

        if( me->query_temp("sitted"))
                return notify_fail("���Ѿ����ڡ����������ˣ�\n");

        if( query("yang")){
                write(query("yang")->name()+"�Ѿ�վ�������������ˣ�\n");
		tell_object(query("yang"),"������"+me->query("name")+"Ҳ��վ������\n");
                return 1;
        }

        message_vision("$N����վ�����������ͼ��\n", me);

        if ( me->query_skill("qimen-wuxing", 1) < 150 &&
             !present("he tu", me) && !present("luo shu", me) )
	{		
		tell_object(me,MAG"��ֻ����Ѫ��ӿ�����������������Ϯ����\n"NOR);
		me->unconcious();
                return 1;
        }
	message_vision(HIY"$N�����鲽�Ⱥ�����Է�λ������������죬Ƭ�̼������ﲻ���ڻ���\n"NOR,me);
	me->set_temp("standed", 1);
	set("yang", me);

        return 1;
}

int do_leave()
{
	object me;

	me = this_player();
	if (me->query_temp("sitted")) {
		me->delete_temp("sitted");
		delete("yin");
		message_vision("$N����һ��������������վ��������\n",me);
	}

        if (me->query_temp("standed")) {
                me->delete_temp("standed");
                delete("yang");
		message_vision("$N��ϢƬ�̣�ͣס����������ȥ�е�ƣ�롣\n",me);
	}

	return 1;
}

int valid_leave(object me, string dir)
{
	if (me->query_temp("sitted") || me->query_temp("standed"))
		return notify_fail("���������δ��(leave)��óȻ�뿪̫��ͼ�������ˣ�\n");
	return ::valid_leave(me, dir);
}
