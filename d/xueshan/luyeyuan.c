//Rama modified for hx 05/02
#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
        object ob;

        set("short", "¹ҰԷ");
        set("long", @LONG
һ����������������Ī���·���ӿ������С·��Ȼ���ʣ����
��ǰ����һ�鳤������ݺͲ�֦ʲ�������֣���ֻ¹��Ծ����С��߽�
���֣���Ҷ��ϥ�һ��˫������䣬����һ����(lianzuo)��������
ᦸǡ�������¹���ʯ��������ʢ���㻨����ľ��
LONG
        );

        set("exits", ([
                "east" : __DIR__"houyuan",
        ]));
        set("item_desc", ([
                "lianzuo" : "�������м�����̳����档\n",
        ]));
        set("cost", 2);
        set("outdoors","qilian-shan");
        setup();
        ob=new("/d/xueshan/obj/lx-jing");
        if (ob)
        ob->move(__DIR__"luyeyuan");
}

void init()
{
        add_action("do_sit", "sit");
        add_action("do_stand", "stand");
        add_action("do_understand", "understand");
        add_action("do_understand", "lingwu");
}

int do_sit(string arg)
{
        mapping skl;
        object me=this_player();
        string *sname;
        int i,j;

        if( !arg || arg!="lianzuo" ) return 0;

        if( me->query_temp("sitted"))
                return notify_fail("���Ѿ����������ˣ�\n");

        if( query("zuo")){
                write(query("zuo")->name()+"�Ѿ����������ˣ�\n");
                tell_object(query("zuo"), "������"+me->query("name")+"Ҳ����������\n");
                return 1;
        }
        skl = me->query_skills();
        sname  = keys(skl);

        if( arg == "lianzuo"){
        message_vision("$N̤����������ס����涫������\n", me);

        if ( me->query_skill("lamaism", 1) < 150){
                me->unconcious();
                return 1;
        }

                message_vision(HIY"��ľ������ȼ��$N�����������������֪���Ȼ�԰�������������������͡�\n"NOR, me);
                me->set_temp("sitted", 1);
                set("zuo", me);
                return 1;
        }
        return 1;
}
int do_stand()
{
        if (this_player()->query_busy())
                return notify_fail("�㻹����վ������\n");

        message_vision("$Nվ������������������\n", this_player());
        this_player()->delete_temp("sitted");
        set("zuo", 0);
        return 1;
}
int valid_leave(object me, string dir)
{
        if (me->query_temp("sitted"))
        return notify_fail("�����ߣ�\n");
        return ::valid_leave(me, dir);
}
int do_understand(string arg)
{
        object me;
        string skillname;
        int skill_special, skill_basic;

        me = this_player();

        if (!me->query_temp("sitted")) return 0;

        if( !arg )
                return notify_fail("��Ҫ�о����ֻ����似��");

        if( arg == "force" )
                return notify_fail("�㲻���������������ڹ���\n");

        if (me->is_busy())
                return notify_fail("��������æ���ء�\n");

        if( me->is_fighting() )
                return notify_fail("���Ѿ���ս�����ˣ�ѧһ��ʵս����ɡ�\n");

        if( !stringp(skillname = me->query_skill_mapped(arg)) )
                return notify_fail("������������书����������似��������\n");

        skill_basic = me->query_skill(arg, 1);
        skill_special = me->query_skill(skillname, 1);

        if( skill_special < 1 )
                return notify_fail("����ⷽ��ļ��ܻ���һ�ϲ�ͨ����ô��ȴӻ���ѧ��\n");
        if( skill_basic > skill_special )
                return notify_fail("��" + to_chinese(skillname) + "�����������޷���������" + to_chinese(arg) + "��\n");
        if( skill_basic < 1 )
                return notify_fail("�����û��ѧ������������ܰɣ� �����ȥ��̱��ˡ�\n");

        if ( me->query("jing") < 100 )
                return notify_fail("�����ھ��񲻼ѣ��޷���������˼����\n");

        if( (int)me->query("potential") - (int)me->query("learned_points") <= 1 )
                return notify_fail("���Ǳ�ܲ��㣬�޷���������书��\n");

        me->receive_damage("jing", random(skill_basic));

        if(random(20) == 0) {
        me->add("potential", -2);
                me->improve_skill(arg, skill_special + random(skill_special*2));
                write( "ֻ�����л�Ȼ���ʣ����" + to_chinese(arg) + "�������ֽ���һ�㣡\n" );
        }
        else if(random(10) == 0) {
                me->add("potential", -1);
                me->improve_skill(arg, skill_special/2 + random(skill_special/1));
                write( "��ڤ˼���룬��" + to_chinese(arg) + "��������һ����ᣡ\n" );
        }
        else if(random(5) == 0) {
                me->add("potential", 0);
                me->improve_skill(arg, skill_special/4 + random(skill_special/2));
                write( "�����ֱȻ��ţ��ƺ���" + to_chinese(arg) + "�еļ�������������ᡣ\n" );
        }
        else if(random(2) == 0) {
                me->improve_skill(arg, skill_special/8 + random(skill_special/4));
                write( "������������Ǳ�Ŀ�˼" + to_chinese(arg) + "�ϵ��ѽ�֮����\n" );
        }
        else if(random(5) == 0) {
                write( "������˵�����ķ����" + to_chinese(arg) + "ʼ�ղ���һ�⡣\n" );
        }
        else if(random(10) == 0) {
                me->improve_skill(arg, - (skill_special/10 + random(skill_special/5)));
                write( "��ֻ�������������Ҵܣ�" + to_chinese(arg) + "�е���ʽ�������һ������ǰ���֣�\n" );
        }
        else if(random(20) == 0) {
        me->improve_skill(arg, - (skill_special/6 + random(skill_special/3)));
                write( "��Ĵ�����һƬ�հס���" + to_chinese(arg) + "��Խ��Խ��Ϳ��\n" );
        }
        else {
                write( "������������Ǳ�Ŀ�˼" + to_chinese(arg) + "�ϵ��ѽ�֮����\n" );
        }

        if( (int)me->query("potential") - (int)me->query("learned_points") < 0) me->set("potential", (int)me->query("potential") - (int)me->query("learned_points"));

        return 1;
}
        

