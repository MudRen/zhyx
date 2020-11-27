// top.c

#include <ansi.h>
#include <mudlib.h>

inherit F_CLEAN_UP;
int top_list(object ob1,object ob2);
int get_score(object ob);

int main(object me, string arg)
{
        
        object *list,*ob;
        int i;
        string msg;

        if (!wizardp(me))
        return notify_fail("Ŀǰ�ݲ�����ҿ��š�\n");

        ob = filter_array(objects(), (: userp($1) && !wizardp($1) :));
        list = sort_array(ob, (: top_list :));
        msg =  "\n                �� "+BCYN HIW+"�л�Ӣ�����߸������а�"NOR" ��\n";
        msg += "�������������ө��ߩ����������������ө������ө��������ө��ߩ����ө�����������\n";
        msg += "��   ����   ��    ��        ��    �� ���� �� ��  �� �� ��  �� ��  ��  ��  ��\n";
        msg += "�ĩ����������ة��������������������ة������ة��������ة��������ة�����������\n";

        if (arg == "80") {
        for (i = 0 ;i < 80 ; i++) {
        if( i >= sizeof(list)) msg += "����ʱ��ȱ�� \n";
                else {
                if(list[i] == me) msg += BBLU HIY;
//              msg += sprintf("��    %-7s %-22d%-4d %-10d %7d  ��\n"NOR,
                msg += sprintf("��    %-7s", chinese_number(i+1));
                msg += sprintf("%-22s", (list[i]->query("name")?list[i]->query("name"):"������")+"("+((list[i]->query("id"))?(list[i]->query("id")):"un known")+")"),
                msg += sprintf("   %-4d", list[i]->query("age"));
                msg += sprintf("     %-10s ", list[i]->query("family")?list[i]->query("family/family_name"):"��ͨ����");
                msg += sprintf("%-6d   ", list[i]->query("max_neili"));
                msg += sprintf("%7d  ��\n", get_score(list[i]));
                }
                         }
       msg += "����������������������������������������������������������������������������\n";

//     reset_eval_cost();
       msg += "  " + NATURE_D->game_time() + "�ǡ�\n";
       write(msg);
       return 1;
        }
        if (arg == "50") {
        for (i = 0 ;i < 50 ; i++) {
        if( i >= sizeof(list)) msg += "����ʱ��ȱ�� \n";
                else {
                if(list[i] == me) msg += BBLU HIY;
//              msg += sprintf("��    %-7s %-22d%-4d %-10d %7d  ��\n"NOR,
                msg += sprintf("��    %-7s", chinese_number(i+1));
                msg += sprintf("%-22s", (list[i]->query("name")?list[i]->query("name"):"������")+"("+((list[i]->query("id"))?(list[i]->query("id")):"un known")+")"),
                msg += sprintf("   %-4d", list[i]->query("age"));
                msg += sprintf("     %-10s ", list[i]->query("family")?list[i]->query("family/family_name"):"��ͨ����");
                msg += sprintf("%-6d   ", list[i]->query("max_neili"));
                msg += sprintf("%7d  ��\n", get_score(list[i]));
                }
                         }
       msg += "����������������������������������������������������������������������������\n";

//     reset_eval_cost();
       msg += "  " + NATURE_D->game_time() + "�ǡ�\n";
       write(msg);
       return 1;
        }
        if (arg == "30") {
        for (i = 0 ;i < 30 ; i++) {
        if( i >= sizeof(list)) msg += "����ʱ��ȱ�� \n";
                else {
                if(list[i] == me) msg += BBLU HIY;
//              msg += sprintf("��    %-7s %-22d%-4d %-10d %7d  ��\n"NOR,
                msg += sprintf("��    %-7s", chinese_number(i+1));
                msg += sprintf("%-22s", (list[i]->query("name")?list[i]->query("name"):"������")+"("+((list[i]->query("id"))?(list[i]->query("id")):"un known")+")"),
                msg += sprintf("   %-4d", list[i]->query("age"));
                msg += sprintf("     %-10s ", list[i]->query("family")?list[i]->query("family/family_name"):"��ͨ����");
                msg += sprintf("%-6d   ", list[i]->query("max_neili"));
                msg += sprintf("%7d  ��\n", get_score(list[i]));
                }
                         }
       msg += "����������������������������������������������������������������������������\n";

//     reset_eval_cost();
       msg += "  " + NATURE_D->game_time() + "�ǡ�\n";
       write(msg);
       return 1;
        }
    else
        for (i = 0 ;i < 10 ; i++) {
        if( i >= sizeof(list)) msg += "����ʱ��ȱ�� \n";
                else {
                if(list[i] == me) msg += BBLU HIY;
//              msg += sprintf("��    %-7s %-22d%-4d %-10d %7d  ��\n"NOR,
                msg += sprintf("��    %-7s", chinese_number(i+1));
                msg += sprintf("%-22s", (list[i]->query("name")?list[i]->query("name"):"������")+"("+((list[i]->query("id"))?(list[i]->query("id")):"un known")+")"),
                msg += sprintf("   %-4d", list[i]->query("age"));
                msg += sprintf("     %-10s ", list[i]->query("family")?list[i]->query("family/family_name"):"��ͨ����");
                msg += sprintf("%-6d   ", list[i]->query("max_neili"));
                msg += sprintf("%7d  ��\n", get_score(list[i]));
                }
                         }
       msg += "����������������������������������������������������������������������������\n";

//     reset_eval_cost();
       msg += "  " + NATURE_D->game_time() + "�ǡ�\n";
       write(msg);
       return 1;
}
int top_list(object ob1, object ob2)
{
      int score1,score2;

        score1 = get_score(ob1);
        score2 = get_score(ob2);

      return score2 - score1;
}

int get_score(object ob)
{
        int tlvl,i,score;
        string *ski;
        mapping skills;

      reset_eval_cost();
        skills = ob->query_skills();
        if (!sizeof(skills)) return 1;
        ski  = keys(skills);
        for(i = 0; i<sizeof(ski); i++) {
                        tlvl += skills[ski[i]];
                        }  // count total skill levels
/*
        score = tlvl/10;
        score += ob->query("max_neili")/10;
        score += ob->query_str() + ob->query_int() + ob->query_dex() + ob->query_con();
        score += (int)ob->query("combat_exp")/2500;
*/
        score = ob->query("combat_exp");
        return score;
}

int help(object me)
{
write(@HELP
ָ���ʽ : top

���ָ���������֪�����ߵĸ��֡� 

������

top 30     �鿴����ǰ30λ����
top 50     �鿴����ǰ50λ����
top 80     �鿴����ǰ80λ����
 
HELP
    );
    return 1;
}
