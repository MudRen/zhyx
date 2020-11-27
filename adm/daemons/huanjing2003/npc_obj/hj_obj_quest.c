//                ��׼��������ʾ��                                   |
// �þ�����Ʒ  �����ͣ�����ѧϰ���ܵ����ͣ�
// by naihe  2002-10-23  ��ï��
// �����ֻ��Ϊѧϰ�����͵���Ʒʹ�á� 21:42 02-10-28 by naihe
// naihe 05-9-7 9:15 v1.7 ����������

#include <ansi.h>

inherit ITEM;

string *names=({
    HIW"����֮ʯ"NOR,
    MAG"����֮ʯ"NOR,
    HIC"����֮ʯ"NOR,
    HIG"����֮ʯ"NOR,
    YEL"��ʯ֮ʯ"NOR,
    RED"�ɻ�֮ʯ"NOR,
    BLU"���֮ʯ"NOR,
    CYN"����֮ʯ"NOR,
    CYN"����֮ʯ"NOR,  // ��һ�������ñ���Ʒ
});

string *ids=({
    "hufeng shi",
    "huanyu shi",
    "luolei shi",
    "yindian shi",
    "gunshi shi",
    "feihuo shi",
    "duohun shi",
    "fuhuo shi",
    "fuhuo shi",
});

string *longs=({
    "����һ�ź���֮ʯ�����ƺ�����һ�����صĸо���\n�㲻����ϸ���(linghui)һ�����ָо���\n",
    "����һ�Ż���֮ʯ�����ƺ�����һ�����صĸо���\n�㲻����ϸ���(linghui)һ�����ָо���\n",
    "����һ������֮ʯ�����ƺ�����һ�����صĸо���\n�㲻����ϸ���(linghui)һ�����ָо���\n",
    "����һ������֮ʯ�����ƺ�����һ�����صĸо���\n�㲻����ϸ���(linghui)һ�����ָо���\n",
    "����һ�Ź�ʯ֮ʯ�����ƺ�����һ�����صĸо���\n�㲻����ϸ���(linghui)һ�����ָо���\n",
    "����һ�ŷɻ�֮ʯ�����ƺ�����һ�����صĸо���\n�㲻����ϸ���(linghui)һ�����ָо���\n",
    "����һ�Ŷ��֮ʯ�����ƺ�����һ�����صĸо���\n�㲻����ϸ���(linghui)һ�����ָо���\n",
    "����һ�Ÿ���֮ʯ�����ƺ�����һ�����صĸо���\n�㲻����ϸ���(linghui)һ�����ָо���\n",
    "����һ�Ÿ���֮ʯ�����ƺ�����һ�����صĸо���\n�㲻����ϸ���(linghui)һ�����ָо���\n",
});

string *units=({
    "��",
    "��",
    "��",
    "��",
    "��",
    "��",
    "��",
    "��",
    "��",
});

string *skills=({
    "hfzj",
    "hyzj",
    "llzj",
    "ydzj",
    "gszj",
    "fhzj",
    "dhzj",
    "heal",
    "heal",
});

string *skills_names=({
    "����֮��",
    "����֮��",
    "����֮��",
    "����֮��",
    "��ʯ֮��",
    "�ɻ�֮��",
    "���֮��",
    "�ָ�֮��",
    "�ָ�֮��",
});

int *sks_damages=({   // ��ѧʱ�ܵõ��� Ч�����ȼ���
    3+random(3),
    3+random(3),
    3+random(3),
    3+random(3),
    5,
    5,
    3,
    5+random(6),
    5+random(6),
});


void setme( int iii )
{
    if( iii == 99 ) iii = random( sizeof(names) );
    set( "iii", iii );
    set_name(names[ iii ], ({ids[ iii ],"shi"}));
    set_weight(100);
    if (clonep())
        set_default_object(__FILE__);

    set("long", longs[ iii ]);
    set("unit", units[ iii ]);
    set("hj_game/obj","quest");

    set("value", 1);  // ��������º󲻻���ʧ��
    set("use_times", 5 + random(4)); // ������5-8��
    set("no_refresh",1); // ���ᱻ������¡�
}

void create()
{
    setme( 99 );
    setup();
}

void init()
{
    add_action("do_linghui", ({ "linghui", "lh"}) );
}

void delete_me()
{
    message_vision("$N�����Ѿ������ء���һ����ʧ�ˡ�\n"NOR,this_object());
    destruct(this_object());
}

int do_linghui(string arg)
{
    object me,ob;
    string temp;
    int iii = query("iii"), lh_fail;

    if(query("delete_now")) return 0;

    ob=this_object();
    me=this_player();

    if( !environment(me) || !environment(me)->query("room_mark") )
        return 0;

    if( environment(me)->query("room_mark") == 1 )
        return notify_fail("����ط�������Ἴ�ܡ�\n");
    if(!arg || (arg != ob->query("id") && arg != skills[ iii ] && arg != "shi") )
        return 0;

    if( !me->query_temp("huanjing") || me->query_temp("huanjing") != "start" ||
        !me->query_temp("hj_hp") || me->query_temp("hj_hp") < 1 )
        return 0;
    if( me->is_busy() || me->query_temp("hj_need_waiting") )
        return notify_fail("�㻹æ���ء�\n");

    if( me->query_temp("hj_hp") <50 )
        return notify_fail("���Ѿ�ͷ���ۻ��ˣ���������Ϣ��Ϣ�ɡ�\n");

    message_vision(CYN"$N"NOR+CYN"����$n"NOR+CYN"��ϸ�����ţ����������������������Ϣ��\n"NOR,me, ob);
    me->add_temp("hj_hp",-(5+random(6)));

    lh_fail = random(3);  // 0, 1, 2.  0 ʱ���ǳɹ���
    // ��֮���ȱ�������Ч��  �������ʯ�ļ���ʱ���ɹ��������ǡ�
    // ʧ���˵Ļ�������һ�λ���
    if( lh_fail && me->query_temp("hj_special/cm") )
        lh_fail = random(3);    // 0, 1, 2.  0 ʱ���ǳɹ���
    if( lh_fail )
        message_vision(CYN"$N"NOR+CYN"�ƺ�ʮ��ƣ����ȴ�����޷�ץס����Ʈ��֮�С�\n"NOR,me);
    else
    {
        if( !me->query_temp("hj_game_skills/"+skills[ iii ])
          || !me->query_temp("hj_game_damages/"+skills[ iii ])
        )
            temp="new";
        else
            temp="up";
        if(temp == "new")
        {
            me->set_temp("hj_game_skills/"+skills[ iii ],skills_names[ iii ]);
            me->set_temp("hj_game_damages/"+skills[ iii ],sks_damages[ iii ]);
            message_vision(CYN"$N"NOR+CYN"ֻ����ͻȻ֮������������ʾ���������ˡ�"+skills_names[ iii ]+"����\n"NOR,me);
        }
        else
        {
            if(me->query_temp("hj_game_damages/"+skills[ iii ]) >= 99)
                message_vision(CYN"$N"NOR+CYN"ֻ�����������壬�������Ѱ���ȫ������ˡ�\n"NOR,me);
            else
            {
                me->add_temp("hj_game_damages/"+skills[ iii ], 1 );
                message_vision(CYN"$N"NOR+CYN"ֻ����ͻȻ֮���ľ����壬�ԡ�"+skills_names[ iii ]+"��������ֽ���һ�㣡\n"NOR,me);
            }
        }
    }
    me->start_busy(1);      // æʱ�µ���
    add("use_times", -1);
    if( !random(2) || query("use_times") < 1 )
    {
        if( query("wait_delete") )
        {
            set("delete_now", 1);
            remove_call_out("delete_me");
            call_out("delete_me",1);
        }
        set("wait_delete",1);
    }
    return 1;
}
