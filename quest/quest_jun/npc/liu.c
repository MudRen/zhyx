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
string ask_fengshang();
string ask_chubing();
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
                 "����" :   (: ask_fengshang :),  
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

string ask_chubing()
{
       	object me = this_player(), ob = this_object();
       	object bingfu, kaijia;
       	string temp;
       	int liangcao, i, reward;

       	if (me->query_condition("junquest_fail"))
       		return "�������Ǵ���֮�����Գ������������ѱ�����������ذɣ�\n";
       	if (me->query_condition("junquest_song"))
       		return "�����Ѿ������������ˣ���������ĥ��ʲô������\n";
       	if (me->query("degree_jungong") < 8)
       		return "���˹ٵ�λ�����������һ��֮˧���ѷ������ģ���\n"; 

       	temp = read_file("/quest/quest_jun/song/master", 1, 1);
       	if (temp != "" && (time() - query("begin/time")) < 4200)
       		return "�����Ѿ������ʾ������ˣ����˿���ǰȥ����\n";

       	me->set_temp("jun_quest/party", "song");

       	if (! objectp(kaijia = present("kai jia", me)))
       	{
        	kaijia = new("/quest/quest_jun/song/obj/tiejia");
        	kaijia->move(me);
       	}
       	if (! objectp(bingfu = present("bing fu", me)))
       	{
        	bingfu = new("/quest/quest_jun/song/obj/bingfu");
        	bingfu->set("owner", me->query("id"));
        	bingfu->set("master", me->query("name"));
        	bingfu->move(me);
       	 	bingfu->check_me(me);
       	}
       	write_file("/quest/quest_jun/song/master", "", 1);
       	write_file("/quest/quest_jun/song/master", me->query("id"), 1);
       	liangcao = 1000;
       	temp = sprintf("%d", liangcao);
       	write_file("/quest/quest_jun/song/liangcao", temp, 1);
       	reward = 0;
       	temp = sprintf("%d", reward);
       	write_file("/quest/quest_jun/song/reward", temp, 1);

       	me->set("eff_qi", me->query("max_qi") + 1000 * me->query("degree_jungong"));
       	me->set("qi", me->query("eff_qi"));
       	me->set_temp("jun_quest/train", "infantry");

       	me->apply_condition("junquest_song", 240);
       	remove_call_out("quest_begin");
       	call_out("quest_begin", 10, me->short(1), me);
       	me->set("party/party_name", HIW"����"NOR);
       	me->set("party/rank", HIW"����Ԫ˧"NOR);  
        me->apply_condition("pill_drug", 1000); 
      	me->delete("jun_quest/jiang"); 

       	return HIC"���ˣ����п���֮���Ѿ���ʣ�޼���������Ӫ�������п�һս��\n"
       		+ "�˴γ��������ص�Զ�������¹��Ҵ��ι��ˣ��������˾�����Ϊ��"
       		+ "������\n���յ�ʤ�������س����������Ϊ��������ǧ�����������˽�����\n"NOR;
}

void quest_begin(string who, object me)
{
      	object jiang, jiangjun, kehan, smen, mmen;
      	string temp;
      	int num, i;

      	message("channel:rumor", MAG"������ʷ�ǡ�"
      		+ CHINESE_D->chinese_date((time() - 14 * 365 * 24 * 60 * 60))
      		+ "�������������֣������ɳ�\n " + who + "\n"
      		+ MAG" ����ʦ���Ͽ���.....\n"NOR,
      		users());

      	set("begin/time", time());
      	// By Lonely
      	num = 0;
      	temp = sprintf("%d", num);
      	write_file("/quest/quest_jun/meng/jiang", temp, 1);
      
      	smen = get_object("/quest/quest_jun/syuanmen1");
      	if (objectp(smen))
      	 	smen->set("defence", 120);
      	mmen = get_object("/quest/quest_jun/myuanmen1");
      	if (objectp(mmen))
      		mmen->set("defence", 120);

      	kehan = new("/quest/quest_jun/meng/kehan");
      	kehan->move("/quest/quest_jun/mying1");
      	kehan->change_ob();

      	for (i = 0; i < 3; i++)
      	{              
        	jiang = new("/quest/quest_jun/meng/mengj");
        	jiang->move("/quest/quest_jun/mying");
        	jiang->change_ob();
      	}
      	jiang = new("/quest/quest_jun/meng/mengj");
      	jiang->move("/quest/quest_jun/mying1");
      	jiang->change_ob();

       	for (i = 0; i < 3; i++)
       	{      
        	jiang = new("/quest/quest_jun/meng/mengj");
        	jiang->move("/quest/quest_jun/dhunya");
        	jiang->change_ob();
       	}

       	for(i = 0; i < 4; i++)
       	{
        	jiang = new("/quest/quest_jun/song/songb");
        	jiang->move("/quest/quest_jun/sying1");
        	jiang->change_ob();
       	} 

      	if (me->query("degree_jungong") > 12)
      	for (i = 0; i < 2; i++)
      	{
        	jiangjun = new("/quest/quest_jun/meng/mengj");
        	jiangjun->move("/quest/quest_jun/myuanmen1");
        	jiangjun->change_ob();
      	}

      	if (me->query("degree_jungong") > 10)
      	for (i = 0; i < 2; i++)
      	{
        	jiang=new("/quest/quest_jun/meng/mengj");
        	jiang->move("/quest/quest_jun/caoyuan");
        	jiang->change_ob();
      	}

      	return;
}

string ask_fengshang()
{
        object me = this_player();   
        int reward;
        reward = me->query("jun_quest/reward");

        if (me->query_condition("junquest_fail"))
         	return "�������Ǵ���֮��������Ҫʲô���ͣ���\n";

        if (! intp(reward) || reward < 1)
         	return "����������кι��Ͱ�������ʲô���ͣ���\n";

        if (me->query_temp("ask_fengshang"))
         	return "�����԰����꣬"
                	+ "�ۼ��Ѿ�����ʥ���ˣ����������Ĺ���ʥ��ּ��ɣ�\n";
	remove_call_out("add_fengshang");
        call_out("add_fengshang", 10, me, reward);
        me->set_temp("ask_fengshang", 1);
        return "�������Ժ��ۼ������������ʥ�ϣ�Ϊ�����빦��\n"; 
}

                 
void add_fengshang(object me,int reward)
{                         
        int pot, exp, jungong, i;
        mapping jiang;
        object bingfu;

        if (! objectp(me)) return;

        message("channel:rumor", MAG"�����ξ��ǡ�"NOR + YEL
        	+ CHINESE_D->chinese_date((time() - 14 * 365 * 24 * 60 * 60))
        	+ "......\n"NOR,
        	users());
        if (reward > 60) reward = 60;
	exp = (reward / 2 + random(reward / 2)) * me->query("degree_jungong") * 500; 
        pot = exp / 4; 
        jungong = exp / 1000;
        me->add("guo_shoucheng/reward_exp", exp);
        me->add("guo_shoucheng/reward_potential", pot);
        me->add("guo_shoucheng/reward", jungong);
        me->add("combat_exp", exp);
        me->add("potential", pot);
        me->add("experience", random(21)); 
        me->add("balance", 10000000);
        message("channel:rumor", MAG"�����ξ��ǡ�" HIY "����������ʵ�گԻ��\n"
        	+ me->short(1) + "\n" + HIY"�����й����ͻƽ�ǧ����������ƥ����Ůʮ����"
        	+ " �Ǿ��� "HIR + chinese_number(jungong)
        	+ HIY" �ߣ��մˣ�\n\n"NOR,
        	users());       

        tell_object(me, HIW"������" + HIR + chinese_number(exp)
        	    + HIW"�㾭���" + HIR + chinese_number(pot) 
        	    + HIW"��Ǳ�ܽ�������\n"NOR);
        
        jiang = me->query("jun_quest/jiang");
        if (jiang && sizeof(jiang) > 0)
        for (i = 1; i <= sizeof(jiang); i++)
        {
        	if (! objectp(jiang["jiang" + i]) || ! userp(jiang["jiang" + i])) continue;
        	exp = (reward / 2 + random(reward / 2)) * jiang["jiang" + i]->query("degree_jungong") * 500;
        	pot = exp / 4;
        	jungong = exp / 1000;
        	jiang["jiang" + i]->add("guo_shoucheng/reward_exp", exp);
        	jiang["jiang" + i]->add("guo_shoucheng/reward_potential", pot);
        	jiang["jiang" + i]->add("guo_shoucheng/reward", jungong);
        	jiang["jiang" + i]->add("combat_exp", exp);
        	jiang["jiang" + i]->add("potential", pot);
        	jiang["jiang" + i]->add("experience", random(11)); 
        	jiang["jiang" + i]->add("balance", 5000000);  
        	  
        	message("channel:rumor", MAG"�����ξ��ǡ�" HIY "����������ʵ�گԻ��\n"
        		+ jiang["jiang" + i]->short(1) + "\n" + HIY"�����й����ͻƽ���������������ƥ��"
        		+ " �Ǿ��� "HIR + chinese_number(jungong) + HIY" �ߣ��մˣ�\n\n"NOR,
        		users()); 
        	jiang["jiang" + i]->delete("party");
        	tell_object(jiang["jiang" + i], HIW"������" + HIR + chinese_number(exp)
        		    + HIW"�㾭���" + HIR + chinese_number(pot) + HIW"��Ǳ�ܽ�������\n"NOR);  
        }       
         
        bingfu = present("bing fu", me);       
        if (objectp(bingfu)) destruct(bingfu);
        
        me->delete_temp("jun_quest");
        me->delete("party");
        me->delete("jun_quest");
        me->delete_temp("ask_fengshang");
        me->set("eff_qi", me->query("max_qi"));
        me->set("qi", me->query("eff_qi"));
        write_file("/quest/quest_jun/song/master", "", 1);
        return;
}

