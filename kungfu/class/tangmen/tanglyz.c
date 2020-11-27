// tanglyz

#include <ansi.h>
#include "tangmen.h"

inherit NPC;
inherit F_MASTER;

void create()
{
	set_name("����ү��", ({ "tanglyz", "tang", "yezi"}));
	set("long", 
"����ү�������ŵĿ�ɽ��ʦ�������ŵ�λ�ĸߡ�\n");
	set("gender", "����");
	set("age", 91);
        set("class", "tangmen");
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 28);
        set("max_qi", 8000);
        set("max_jingli", 1500);
        set("max_douzhi", 500);
        set("douzhi", 500);
        set("neili", 4000);
        set("max_neili", 4000);
        set("yanli",200);
        set("jiali", 100);
        set("combat_exp", 800000);
        set("level", 15);
        set("shen",3000);
        set("score", 7000);

        set_skill("force", 480);
        set_skill("throwing", 480);
        set_skill("dodge", 480);
        set_skill("parry", 480);
        set_skill("literate", 480);
        set_skill("hand", 480);
        set_skill("sword", 480);
        set_skill("boyun-suowu", 480);
        set_skill("biyun-xinfa", 480);
        set_skill("sanku-shengong", 480);
        set_skill("qiulin-shiye", 480);
        set_skill("wuzhan-mei", 480);
        set_skill("poison", 400);
        set_skill("medical", 400);
        set_skill("tangmen-throwing", 480);
        set_skill("tangmen-poison", 480);
        set_skill("tangmen-medical", 480);        
        
        map_skill("force", "sanku-shengong");
        map_skill("throwing", "tangmen-throwing");
        map_skill("dodge", "qiulin-shiye");
        map_skill("parry", "wuzhan-mei");
        map_skill("sword", "wuzhan-mei");
        map_skill("hand", "boyun-suowu");
        map_skill("poison", "tangmen-poison");
        map_skill("medical", "tangmen-medical");
        
        prepare_skill("hand", "boyun-suowu");
        
	create_family("��������", 1, "����");

        set_temp("apply/damage", 100);  
        set_temp("apply/unarmed_damage", 100);  
        set_temp("apply/armor", 200);          

        set("master_ob", 5);
	setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/d/tangmen/obj/feidao")->wield();
        carry_object("/d/tangmen/obj/fhshi")->wield();
        carry_object("/d/tangmen/obj/tiejili")->wield();
        carry_object("/d/tangmen/obj/feidao")->wield();
        carry_object("/d/tangmen/obj/fhshi")->wield();
        carry_object("/d/tangmen/obj/tiejili")->wield();
        carry_object("/d/tangmen/obj/qinglianzi")->wield();
        carry_object("/d/tangmen/obj/qinglianzi")->wield();
        set_temp("handing", carry_object("/d/tangmen/obj/jili"));          
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))  
                return;
                
        if ((string)ob->query ("family/family_name") == "��������" && count_gt(ob->query ("combat_exp"), 1000000))
	{
                message_vision("����ү��΢΢һЦ����$N˵��:�����ʦ�Ļ�ȥ����̫̫�ɣ����Ѿ�����ͽ���ˣ���\n",ob);
                message_vision("����ү��΢΢һ�٣��ֵ�:����������Ȼ���Ѿ��ҵ��������ˣ��Ҿ�ָ���㼸�аɣ���\n",ob);
                command("say �ðɣ��ӽ�����������ҵĹ��ŵ����ˡ�\n");
                command("recruit " + ob->query("id"));
	}
	else
		if ( (string)ob->query ("family/family_name") != "��������" )
		{
			message_vision("\n����ү��΢΢һЦ����$N˵��:���㲻֪�������������ң��������յ������\n",ob);
			message_vision("����ү��΢΢һ�٣��ֵ�:����������Ȼ���Ѿ��ҵ��������ˣ��ͺȱ������߰ɣ���\n",ob);
			tell_object(ob, "����ү�Ӽ�����Щ��ԥ��˵��:�������Ǽ�����󣬺��˿��Թ̱���Ԫ����ϰ��֮�˿��Ǵ������氡����\n\n");
			write(YEL"��Ҫ����������ѡ��y)/n ��"NOR);
			input_to("accept_cha", 1, ob, 1);
		}
		else
			tell_object(ob, "����ү����ϧ�Ķ���˵:����ϧ��Ĺ��򻹲����ң�����ʹ���ҵľ��������Ժ������ɣ���\n");
	return;
}

void accept_cha(string want, object ob, int forever)
{
	if ( want == "" || want == "y" || want == "Y" )
	{
		message_vision("����ү��΢һ̧�֣�����һ�Ҷ���$N������һ����裡\n",ob);
		tell_object(ob, "ֻ����ˮ������������ɫ����ð����������Ƭ��֪����ҶƬƯ�ڱ��У������������˱ǡ�\n");
		message_vision("$N���豭���������ĺ���һ�ڡ�\n", ob);
		call_out("dead", 120, ob);
	}
	else
	{
		message_vision("\n����ү�Ӳ�Ȼ��ŭ����$N�ȵ�:����������㲻Ҫ����Ҫ�Ҷ������������ǲ��ܱ�����֪���ģ���\n",ob);
		this_object()->kill_ob(ob);
		ob->fight_ob(this_object());
	}
}

int dead(object ob)
{
	tell_object(ob,HIR"�㸹��ͻȻ�絶��һ����ʹ��ԭ�����о��Ǿ綾......\n����ǰһ�ڣ�һͷ�Ե��ڵ���......"NOR);
	tell_room( environment(ob), HIR + ob->query("name") + "ͻȻһͷ�Ե��ڵ��ϣ�"NOR, ob);
	ob->set_temp("die_reason", "�������涾����");
	ob->die();
	tell_room( environment(this_object()), "����ү�ӳ�̾һ��:������������ô�ᴳ�������أ���");
}
