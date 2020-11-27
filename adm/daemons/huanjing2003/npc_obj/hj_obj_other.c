//                ��׼��������ʾ��                                   |
// �þ�����Ʒ  �������ͣ���������HP����Ʒ��
// by naihe  2002-10-25  ��ï��

#include <ansi.h>

inherit ITEM;


string *names=({
    "������",
    "���˹�",
    "����֮��",
    "������",
    "Ұ����ʵ",
    ""HIR"��ɫ��ʯ"NOR"",
    ""HIG"��ɫ��ʯ"NOR"",
    ""HIB"��ɫ��ʯ"NOR"",
    ""YEL"����֮��"NOR"",
});

string *ids=({
    "wm guo",
    "xr guo",
    "tq guo",
    "dl guo",
    "ys guo",
    "red baoshi",
    "green baoshi",
    "blue baoshi",
    "sl guo",
});

string *heal_hps=({
    "yes",
    "yes",
    "yes",
    "yes",
    "yes",
    "no",
    "no",
    "no",
    "yes",
});

string *longs=({
    "����һö��С�Ĳ�֪���Ĺ�ʵ������԰�������(chixia)��\n",
    "����һöСС�Ĺ��ӣ����С����˹������ഫ�������ǳ������ӵ��еĶ�����\n����԰�������(chixia)��\n",
    "��ö���ӹ�ģ�����ģ���ȴ�в�Ѫ�����Ĺ�Ч������԰�������(chixia)��\n",
    "����һö���������ഫ��Զ�Ŷ������������˵Ĺ�Ʒ��\n�������(chixia)�˿ɲ�֪���ᷢ��ʲô�¡�\n",
    "����һöҰ����ʵ�����������洦�ɼ�������԰�������(chixia)��\n",
    "����һ�ź�ɫ�ı�ʯ��ɢ�������˵����Ĺ�â��\n",
    "����һ����ɫ�ı�ʯ��ɢ�������˵����Ĺ�â��\n",
    "����һ����ɫ�ı�ʯ��ɢ�������˵����Ĺ�â��\n",
    "����һö������֮�����������ر�����Ĺ�Ч������԰�������(chixia)���Կ���\n",
});


void setme( int iii )
{
    if( iii == 99 ) iii = random( sizeof(names) );
    set("iii", iii );

    if( iii < 5 ||  iii == 8)
        set_name(names[ iii ], ({ids[ iii ],"guo"}));
    else set_name(names[ iii ], ({ids[ iii ] , "baoshi", "bao shi", "bs" }));

    set_weight(100);

    if (clonep())
        set_default_object(__FILE__);

    set("long", longs[ iii ]);
    set("heal_hp",heal_hps[ iii ]);
    set("unit", "ö");
    set("value", 0);  // �������º���ʧ
    //set("no_refresh", 1); // ��������MUDˢ��

    set("hj_game/obj","other");
}


void create()
{
    setme( 99 );
    setup();
}

void init()
{
    if( query("heal_hp") == "yes") add_action("do_chixia","chixia");
}

int do_chixia(string arg)
{
    object ob,me;
    int temp,temp1,temp_add;

    if( !environment(this_player())->query("room_mark") && !wizardp(this_player()))
        return 0;

    me=this_player();
    ob=this_object();

    if( !arg || me->query_temp("huanjing") != "start" || me->query_temp("hj_hp") < 1 )
        return 0;

    if(!me->query_temp("hj_hp_max")) return 0;
    if(!me->query_temp("hj_game_mepower") ) return 0;

    if( query("heal_hp") != "yes" || !arg || !id(arg) )
        return 0;
    //if(me->is_busy()) return notify_fail("�㻹æ���أ�С�ĳ���ҭ�š�\n");
    // ������æʱ�������Ʒûʲô���ô���

    if(ob->query("id") == "sl guo")
    {
        if( !random(3) )
        {
            if( random(3) )
            {
                message_vision(CYN"$N"NOR+CYN"����һ"+ob->query("unit")+ob->query("name")+""NOR+CYN"����ʱ���þ���һ���ƺ�������ǿ��һ�㣡\n"NOR,me);
                me->add_temp("hj_game_mepower",1 );
            }
            else
            {
                message_vision(CYN"$N"NOR+CYN"����һ"+ob->query("unit")+ob->query("name")+""NOR+CYN"����ʱ���þ���һ������������Ϣӿӿ������\n"NOR,me);
                me->add_temp("hj_hp_max", 10 + random(11) );
            }
        }
        else
        {
            message_vision(CYN"$N"NOR+CYN"����һ"+ob->query("unit")+ob->query("name")+""NOR+CYN"���������н�ʹ�������ǳ������ж��Ķ�����\n"NOR,me);
            me->add_temp("hj_hp", - (20+random(31)) );
        }

        destruct(ob);
        return 1;
    }

// �����Ƿ񱥺Ͷ��ܳԣ������Ҳ�ͼӵ� MAX HP ��
// ���Ǳ���״̬�³ԣ���������æʱ��
// ������æʱ��

    temp = me->query_temp("hj_hp");

    if(temp >= me->query_temp("hj_hp_max") )
    {
        me->start_busy(2);
        tell_object(me,"��Եñ����ģ�����ҭס�ˡ�\n");
    }

    switch( ob->query("id") )
    {
        case "wm guo":temp_add=10+random(11);break;   //  10-20
        case "tq guo":if(random(2)) temp_add=1;  //  1 or 30
            else temp_add=30;break;
        case "xr guo":temp_add=30+random(21);break;   //  30-50
        case "dl guo":temp_add=100-random(150);break; //  -50  -  100
        case "ys guo":temp_add=10;break;              //  10
    }
    temp_add *= 3;  // ��ǿЧ��

    temp1 = 1 + temp_add + temp;

    if( temp1 > me->query_temp("hj_hp_max") )
        temp1 = me->query_temp("hj_hp_max");

    me->set_temp("hj_hp",temp1);
    if( temp_add>=0 )
    message_vision(CYN"$N"NOR+CYN"����һ"+ob->query("unit")+ob->query("name")+""NOR+CYN"����ʱ���þ���һ��\n"NOR,me);
    else 
    message_vision(CYN"$N"NOR+CYN"����һ"+ob->query("unit")+ob->query("name")+""NOR+CYN"��ֻ���ø����ʹ�������ǳ������ж��Ķ�����\n"NOR,me);

    destruct(ob);
    return 1;
}
