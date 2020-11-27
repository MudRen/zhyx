#include <ansi.h> 
#include <mudlib.h>

inherit ITEM;

int top_list(object ob1, object ob2);
int get_score(object ob);

void create()
{
        set_name(HIW "ʮ�󿹴���������а�" NOR, ({ "con wall", "con"}));
        set_weight(500000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "\n����һ��������ī��������ɵ�ʮ�󿹴���������а�����"
                            "���ŵ���������\n������ߵ�ʮ�󿹴�������"
                            "����ͨ��(view)������������\n" NOR);
                set("no_get", "�üһ��ǽ���뿹������\n");
                set("unit", "��");
                set("value", 1000000);
                set("material", "stone");
        }
        setup();
        move("/d/city/dongdajie1");
}

void init()
{
        add_action("do_view", "view");
}

int do_view(string arg)
{
        object *list, *ob, me;
        int i;
        string msg;

        me = this_player();

        if (arg != "heros wall" && arg != "heros" && arg != "wall")
                return notify_fail("������Ķ�ʲô��\n");

        // ��ֹϵͳ��Դ���Ĺ�����ʱ�����
        if (! wizardp(me) && time() - me->query_temp("last_view") < 100)
                return notify_fail(HIW "\nͻȻ��Ӣ�۱���һ���⻪������ʹ��"
                                   "���Ա�����ϵ��ּ���\n" NOR);

        ob = filter_array(objects(), (: userp($1) && ! wizardp($1) :));

        list = sort_array(ob, (: top_list :));

        msg =  HIW "\n            ��������" HIG " �� �� �� �� " HIW "��������\n";
        msg += "���������ө��ߩ����������������ө����ߩ��ө���������\n";
        msg += "�� " HIG "����" HIW " ��    " HIG "��        ��" HIW
               "    �� " HIG "��  ��" HIW " �� " HIG "��  ��" HIW " ��\n";
        msg += "�ĩ������ة��������������������ة��������ة���������\n";

        for (i = 0; i < 10; i++)
        {
                if (i >= sizeof(list))
                {
                        msg += HIW "����ʱ��ȱ�� \n" NOR;
                        continue;
                }
                msg += sprintf(HIW "��" HIG "  %-5s %-22s%-10s %5d  " HIW "��\n" NOR,
                        chinese_number(i + 1),
                        list[i]->query("name") + "(" +
                        capitalize(list[i]->query("id")) + ")",
                        list[i]->query("family") ?
                        list[i]->query("family/family_name") : "����ȱ��",
                        get_score(list[i]));
        }
        msg += HIW "����������������������������������������������������\n" NOR;
        msg += HIG + NATURE_D->game_time() + "�ǡ�\n" NOR;
        msg += WHT "Ӣ�۱�������һ��С�ֿ��ţ�" + me->query("name") + "��Ŀǰ���ۣ�" +
               get_score(me) + "��\n\n" NOR;

        write(msg);
        me->set_temp("last_view", time());
        return 1;

}

int top_list(object ob1, object ob2)
{
        int score1, score2;

        score1 = get_score(ob1);
        score2 = get_score(ob2);

        return score2 - score1;
}

int get_score(object ob)
{
        int i, score;

        reset_eval_cost();

        score = ob->query("max_neili") / 10;
        score += ob->query("max_jingli") / 10;
        score += ob->query("max_qi") / 10;
        score += ob->query("max_jing") / 10;
        return score;
}