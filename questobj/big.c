// jin-nang by zzfy
#include <ansi.h>
inherit ITEM;
void create()
{
        string *order=({HIB"��ɫ����"NOR, HIR"��ɫ����"NOR, HIY"��ɫ����"NOR,HIW"��ɫ����"NOR,HIM"��ɫ����"NOR,HIC"��ɫ����"NOR});
        set_name((order[random(6)]) , ({ "jin-nang", "jin","nang"}) );
        set_weight(1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long",
                HIY "һ���ý�˿��ɵĽ��ң��ƺ�����(open)�򿪡�\n"NOR);
                set("unit","��");
                set("value", 0);
        }
        }
void init()
{
        add_action("open_gongbao","open");
}
int open_gongbao(string arg)
{
        int exp;
        int pot;
        int sscore;
        if ( arg == "jin-nang"){
        exp = 2500 + random(2500);
        pot = 350 + random(350);
        sscore = 35 + random(25);
        message_vision(HIM"$N���˲���ͷ�ĺ�ˮ���Ȳ��������ò�����˫�ִ��˽��ҡ�\n"NOR,this_player());
        this_player()->add("combat_exp",exp);
        this_player()->add("potential",pot); 
        this_player()->add("score",sscore);
        tell_object(this_player(),HIR"�ۣ��������㱻�����ˣ�\n\n" +
        chinese_number(exp) + "��ʵս���顣\n"+
        chinese_number(pot) + "��Ǳ�ܡ�\n" +
        chinese_number(sscore) + "���ۺ����ۡ������Ŭ��������\n"NOR);
        destruct(this_object());
        return 1;
     }
     return 0; 
}
