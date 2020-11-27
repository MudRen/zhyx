// Updated by Lonely

#include <ansi.h>
inherit NPC;

string *degree_desc = ({
       HIR "�ܶ�" NOR,
       MAG "��������" NOR,
       MAG "��������" NOR,
       HIB "�򱱽ڶ�ʹ" NOR,
       HIB "���ִ󽫾�" NOR,
       HIW "�����Ԫ˧" NOR,
});
string clear_degree(string arg);
string ask_chubing(object me);
int ask_degree();
int add_degree(object ob, int lv); 

void create()
{
        set_name("������", ({"liu gonggong", "liu"}));   
        set("gender", "����");
        set("age", random(20) + 20);

        set("long", "����һ�����ǻʹ��е�һ��̫�࣬����Ϊ�ʵ۴����౾��\n");
        set("combat_exp", 800000);
        set("attitude", "peaceful");
        set("max_qi", 3000);
        set("max_jing", 2000);
        set("max_neili", 2000);
        set("neili", 1000);
        set("no_get", 1);
        set("inquiry", ([
                 "�߷�" :   (: ask_degree :),  
                 "����" :   (: ask_chubing :),    
     	]));

        setup();
        carry_object("clone/cloth/cloth")->wear();
}            

int ask_degree()
{
        int lv;
        object ob = this_player();

        if (ob->query_temp("degree_jungong") )
        {
         	command("say �����԰����꣬"
                	+ "�ۼ��Ѿ�����ʥ���ˣ����������Ĺ���ʥ��ּ��ɣ�\n");
         	return 1;
        }

        if (ob->query("guo_shoucheng/reward") > 
        	(100 * (1 + ob->query("degree_jungong")) * (1 + ob->query("degree_jungong"))))
        lv = ob->query("degree_jungong") + 1;

        if (lv > (sizeof(degree_desc) + 8))
        {
         	command("say �����Ѿ��پӼ�Ʒ��λ��Ȩ�أ��ö࿼��Щ"
                	+ "Ϊ�������������ǣ�\n");
         	return 1;       
        }

        if (lv <= ob->query("degree_jungong") || ob->query("degree_jungong") < 8)
        {
         	command("say Ҫ��ø��ߵĲ߷⣬���������������󲻹�����\n");
         	return 1;
        }

        command("say �������Ժ��ۼ������������ʥ�ϣ�Ϊ������⣡\n");

	remove_call_out("add_degree");
        call_out("add_degree", 10, ob, lv);
        ob->set_temp("degree_jungong",1);
        return 1;
}

int add_degree(object ob, int lv)
{
        string degree, old_degree;
        degree = degree_desc[lv - 9];

        if (ob->query("degree")) old_degree = ob->query("degree");
        else old_degree = "";

        message("channel:rumor", MAG"�����ξ��ǡ�"NOR + YEL
        	+ CHINESE_D->chinese_date((time() - 14 * 365 * 24 * 60 * 60))
        	+ "......\n"NOR,
        	users());

        message("channel:rumor", MAG"�����ξ��ǡ�"HIY"����������ʵ�گԻ��"
        	+ "�߷� " + old_degree + " " + HIW + ob->query("name")
        	+ HIY" Ϊ���� "NOR + degree + HIY"���մˣ�\n"NOR,
        	users());
        ob->delete_temp("degree_jungong");

        if (ob->query("degree"))
        {
         	if (ob->query("degree_ask"))
         		degree = HIM " �� " NOR + clear_degree(ob->query("degree"))
              		       + HIM " �� " NOR + degree + HIM " �� "NOR;
          	else
         		degree = HIM " �� " NOR + clear_degree(ob->query("degree"))
              		       + degree + HIM " �� " NOR;
      	} else
        	degree = HIM " �� " NOR + degree
              	       + HIM " �� " NOR;   

        ob->set("degree_jungong", lv);
        ob->set("degree", degree);
        ob->add("weiwang", lv * 200); 
        return 1;
}

string clear_degree(string arg)
{
       	if ((strsrch(arg, HIR "�ᶽ" NOR) >= 0)
        ||  (strsrch(arg, HIR "�ܶ�" NOR) >= 0) 
        ||  (strsrch(arg, MAG "��������" NOR) >= 0) 
        ||  (strsrch(arg, MAG "��������" NOR) >= 0)
        ||  (strsrch(arg, HIB "�򱱽ڶ�ʹ" NOR) >= 0) 
        ||  (strsrch(arg, HIB "���ִ󽫾�" NOR) >= 0) 
        ||  (strsrch(arg, HIW "�����Ԫ˧" NOR) >= 0) 
        ||  (strsrch(arg, HIM " �� " NOR) >= 0))
       	{
            	arg = replace_string(arg, HIR "�ܶ�" NOR, "");
            	arg = replace_string(arg, MAG "��������" NOR, ""); 
            	arg = replace_string(arg, MAG "��������" NOR, "");
            	arg = replace_string(arg, HIB "�򱱽ڶ�ʹ" NOR, "");   
            	arg = replace_string(arg, HIB "���ִ󽫾�" NOR, "");
            	arg = replace_string(arg, HIW "�����Ԫ˧" NOR, "");
            	arg = replace_string(arg, HIR "�ᶽ" NOR, "");   
            	arg = replace_string(arg, HIM " �� " NOR, "");
       	}
        return arg;
}

string ask_chubing(object me)
{
        object king = WAR_D->query_king();
        me = this_player();

        if (me->query("combat_exp") > 200000000)
                return "��͢���ż������ԣ����������������ܽ��������췴���㻹�ǻ�ȥ�ɣ�\n";
/*
           if (  me->query_condition("pill_drug") > 0) 
                  return RANK_D->query_respect(me) 
                                  +"������Ϣ����,�Ժ������ɣ�\n"; 
*/
        if (me->query_condition("junquest_fail"))
                return "�������Ǵ���֮�����Գ������������ѱ�����������ذɣ�\n";

        if (me->query_condition("junquest_song"))
                return "�����Ѿ������������ˣ���������ĥ��ʲô������\n";
                                
        if (me->query("degree_jungong") < 8)
                return "���˹ٵ�λ�����������һ��֮˧���ѷ������ģ���\n";

        if (objectp(king))
                return "�����Ѿ���" + king->name(1) + "�ʾ������ˣ����˿���ǰȥ����\n";
       
        if (WAR_D->ask_war(me))
        {
                return "���˻��ǿ����̰ɣ��������г̿ɾ��鷳�ˣ�\n";
        }

        return "�ƺ������˵����⣬�㻹������ʦ�ɣ�\n";
}
