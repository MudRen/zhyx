//By rama@lxtx

inherit ITEM;

#include <ansi.h>

string *xc_msg1 =({
        "������������Ĵ�����xc_place��ÿ�����䣬",
        "���ģ������xc_placeת�˼���Ȧ�ӣ�",
        "�������������ϸ�鿴xc_place�������",
        "����ϸ�۲���xc_place�������",
        "����xc_place���ص�Ѳ���˼��飬",
        "��ϸ������xc_place�ϵ�İ����ף�",
        "������ϵ��˴�̽��xc_place���յ������",
        "����������xc_place�����ı仯��",
});
string *xc_msg2 = ({
        "����Ĺ۲�������xc_place��",
        "�����ڵ����������xc_place",
        "�����xc_place",
        "��ĬĬ���������---xc_place",
});

string *xc_msg3 = ({
        "û�з����κο���֮����",
        "һ��������",
        "û���κ��쳣�ļ���",
        "һ��̫ƽ��",
        "һ���ల���¡�",
});

string look_it(object me);
void create()
{
        set_name(HIG"Ѳ������"NOR, ({ "yao pai","pai" }) );
        set_weight(600);
        if( clonep() )                 
        set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", (: look_it :) );
                set("value", 0);
             }   
}

void init()
{
        add_action("do_xunluo","xunluo");
}

int do_xunluo(object me, object ob)
{
        string the_place, msg1, msg2, msg3;
        mapping renwu;
        me=this_player();
        renwu = me->query("bang_quest");
        
        if( !mapp(renwu) )
                return 0;
        
        if( renwu["id"]!="xc")
                return 0;
        
        the_place = base_name(environment(this_player()));
        if (member_array(the_place,renwu["place"]) != -1)
        {
                msg1 = replace_string(xc_msg1[random(sizeof(xc_msg1))],"xc_place",the_place->short());
                msg2 = replace_string(xc_msg2[random(sizeof(xc_msg2))],"xc_place",the_place->short());
                msg3 = xc_msg3[random(sizeof(xc_msg3))];
                renwu["place"] -= ({ the_place });
                tell_object(me, msg1+msg2+msg3+"\n����ȥѲ����һ���ط��ɣ�\n");
        }
        else
                tell_object(me,"��û��Ҫ������Ѳ�߰���\n");
                
        return 1;
}

string look_it(object me)
{
        return "����һ��"HIW"����С����"NOR"��Ѳ�����ơ�"; 
}         

