// person used in quest

inherit CLASS_D("generate") + "/chinese";
inherit F_SSERVER;

int  accept_object(object who, object ob);

void random_move();
int  leave();
int  is_stay_in_room()	{ return 1; }

mapping family_punishers = ([
        "�䵱��"   : ({ CLASS_D("misc") + "/chongxu" }),
        "������"   : ({ CLASS_D("misc") + "/fangsheng" }),
        "��ɽ��"   : ({ CLASS_D("misc") + "/murenqing" }),
        "������"   : ({ CLASS_D("misc") + "/guoxiang" }),
        "�һ���"   : ({ CLASS_D("misc") + "/taogu" }),
        "������"   : ({ CLASS_D("misc") + "/zhong" }),
        "ؤ��"     : ({ CLASS_D("misc") + "/wangjiantong" }),
        "��Ĺ��"   : ({ CLASS_D("misc") + "/popo" }),
        "ȫ���"   : ({ CLASS_D("misc") + "/laodao" }),
        "������"   : ({ CLASS_D("misc") + "/xiaoxian" }),
        "��ң��"   : ({ CLASS_D("misc") + "/liqiushui" }),
        "ѩɽ��"   : ({ CLASS_D("misc") + "/laoseng" }),
        "Ѫ����"   : ({ CLASS_D("misc") + "/hongri" }),
        "���չ�"   : ({ CLASS_D("misc") + "/tonglao" }),
        "Ľ������" : ({ CLASS_D("misc") + "/furen" }),
        "ŷ������" : ({ CLASS_D("misc") + "/laonu" }),
        "�������" : ({ CLASS_D("misc") + "/huyidao" }),
        "���ϻ���" : ({ CLASS_D("misc") + "/duansh" }),
        "����"     : ({ CLASS_D("misc") + "/yangdingtian" }),
        "�������" : ({ CLASS_D("misc") + "/zhanglao" }),
]);

void create()
{
        ::create();
        set("gender",query("gender"));
	set("age", 30 + random(30));
	set("long", "");
	set("attitude", "friendly");
        set("chat_chance", 30);
        set("chat_msg", ({ (: random_move :) }));
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
	}));
        set("scale", 150);
	set_temp("apply/armor", 50);
	set_temp("apply/damage", 50);
	set_temp("born_time", time());
        add_money("gold",2 + random(4));
        keep_heart_beat();
}

void set_from_me(object me,int arg)
{
        mapping hp_status, skill_status, map_status, prepare_status;
        mapping my;
        mapping skill_statusb;
        string *sname, *mname, *pname;
        string *snameb;
        object npc,weapon,punisher;

        int i, temp, myexp, mylvl, k, count, point, jieti;

        npc = this_object();

        if (arg == 1)
        {
                jieti = (int)me->query("tianmo_jieti/times");
                
                //��ν������ϵ���ң�ɱ�����Ը�������
                if (jieti >= 5)
                        npc->set("family/family_name", keys(family_punishers)[random(sizeof(family_punishers))]);
                else
		        npc->set("family",me->query("family"));

	        if (mapp(skill_status = npc->query_skills()))
        	{
                	skill_status = npc->query_skills();
	                sname = keys(skill_status);
	
        	        temp = sizeof(skill_status);
                	for (i = 0; i < temp; i++)
                        	npc->delete_skill(sname[i]);
	        }
	
        	if (mapp(map_status = npc->query_skill_map()))
	        {
        	        mname = keys(map_status);
                	temp = sizeof(map_status);
	                for (i = 0; i < temp; i++)
        	                npc->map_skill(mname[i]);
	        }

	        if (mapp(prepare_status = npc->query_skill_prepare()))
        	{
	                pname = keys(prepare_status);
	
        	        temp = sizeof(prepare_status);
                	for(i = 0; i < temp; i++)
                        	npc->prepare_skill(pname[i]);
	        }

		if (!stringp(npc->query("family/family_name")))
			punisher = load_object("/kungfu/class/misc/smallfish");
		else
		{
			punisher = load_object(family_punishers[npc->query("family/family_name")][0]);
			if (!objectp(punisher))
				punisher = me;
		}

	        if (mapp(skill_status = punisher->query_skills()))
        	{
                	sname = keys(skill_status);
	                for (i = 0; i < sizeof(skill_status); i++)
        	                npc->set_skill(sname[i], skill_status[sname[i]]);
	        }
        
        	if (mapp(map_status = punisher->query_skill_map()))
	        {
        	        mname = keys(map_status);
                	for(i = 0; i < sizeof(map_status); i++)
                        	npc->map_skill(mname[i], map_status[mname[i]]);
	        }


	        if (mapp(prepare_status = punisher->query_skill_prepare()))
        	{
	                pname = keys(prepare_status);
        	        for(i = 0; i < sizeof(prepare_status); i++)
                	        npc->prepare_skill(pname[i], prepare_status[pname[i]]);
	        }

                if ( me->query_skill("qiankun-danuoyi",1) > 0)
                {
                        npc->set_skill("qiankun-danuoyi",1);
                        npc->map_skill("parry","qiankun-danuoyi");
                }

                if ( me->query_skill("douzhuan-xingyi",1) > 0)
                {
                        npc->set_skill("douzhuan-xingyi",1);
                        npc->map_skill("parry","douzhuan-xingyi");
                }

                if ( me->query_skill("taxue-wuhen",1) > 0)
                {
                        npc->set_skill("taxue-wuhen",1);
                        npc->map_skill("dodge","taxue-wuhen");
                }

                if ( me->query_skill("lingbo-weibu",1) > 0)
                {
                        npc->set_skill("lingbo-weibu",1);
                        npc->map_skill("dodge","lingbo-weibu");
                }

                if ( jieti )
                        npc->set("tianmo_jieti/times",jieti);

		if (punisher != me)
			destruct(punisher);

	        hp_status = me->query_entire_dbase();
	        my = npc->query_entire_dbase();

	        my["str"] = hp_status["str"];
	        my["int"] = hp_status["int"];
	        my["con"] = hp_status["con"];
	        my["dex"] = hp_status["dex"];

                my["qi"] = my["eff_qi"] = my["max_qi"] = hp_status["max_qi"];
                my["jing"] = my["eff_jing"] = my["max_jing"] = hp_status["max_jing"];
                my["jingli"] = my["eff_jingli"] = my["max_jingli"] = hp_status["max_jingli"];
                my["neili"] = my["max_neili"]  = hp_status["max_neili"];
                my["jiali"] = npc->query_skill("force") / 2;

	        my["combat_exp"] = hp_status["combat_exp"];

                my["max_qi"]     *= 1.2;
                my["eff_qi"]     *= 1.2;
                my["qi"]         *= 1.2;
                my["max_jing"]   *= 1.4;
                my["eff_jing"]   *= 1.4;
                my["jing"]       *= 1.4;

                my["max_qi"]     += my["max_qi"]*jieti/10;
                my["eff_qi"]     += my["eff_qi"]*jieti/10;
                my["qi"]         += my["qi"]*jieti/10;
                my["max_jing"]   += my["max_jing"]*jieti/10;
                my["eff_jing"]   += my["eff_jing"]*jieti/10;
                my["jing"]       += my["jing"]*jieti/10;

		mylvl = 0;

                if ( !me->query("have_jietied") )
                {
                        if ( mapp(skill_statusb = me->query_skills()) ) 
                        {
                                snameb = keys(skill_statusb);
                                for(k=0; k<sizeof(skill_statusb); k++) 
                                {
                                        if (SKILL_D(snameb[k])->type() != "knowledge")
				        {
					        if ((int)me->query_skill(snameb[k],1) > mylvl)
						        mylvl = (int)me->query_skill(snameb[k],1);
				        }
                                }
                        }
		        mylvl = mylvl * 19 / 20;
                } else
                        mylvl = to_int(pow(my["combat_exp"]*10,0.33333));
        
		if (mylvl < 200)
			mylvl = 200;

                if ( mapp(skill_statusb = npc->query_skills()) ) {
                        snameb = keys(skill_statusb);
                        count = sizeof(skill_statusb);

                        for(k=0; k<sizeof(skill_statusb); k++) {
                                if (SKILL_D(snameb[k])->type() != "knowledge")
				{
					if (snameb[k] == "poison")
						npc->set_skill(snameb[k],200);
					else
	                                        npc->set_skill(snameb[k],mylvl);
				} 
                       }
                }

	        my["jiali"] = npc->query_skill("force") / 2;

		if (objectp(weapon = npc->query_temp("weapon")))
			destruct(weapon);

		if (stringp(npc->query("family/family_name")))
		switch (npc->query("family/family_name"))
		{
			case "�䵱��":
			case "��ɽ��":
			case "������":
			case "�һ���":
			case "ȫ���":
			case "Ľ������":
				weapon = new("/clone/weapon/changjian");
				weapon->move(npc);
				weapon->wield();
				break;
			case "�������":
				weapon = new("/d/fuzhou/obj/xiuhua");
				weapon->move(npc);
				weapon->wield();
				break;
			case "ѩɽ��":
				weapon = new("/clone/weapon/falun");
				weapon->move(npc);
				weapon->set_amount(4);
				weapon->wield();
				break;
			case "�������":
			case "Ѫ����":
				weapon = new("/clone/weapon/blade");
				weapon->move(npc);
				weapon->wield();
				break;
			case "������":
			case "������":
				weapon = new("/clone/weapon/gangzhang");
				weapon->move(npc);
				weapon->wield();
				break;
			case "��Ĺ��":
				weapon = new("/clone/weapon/gangjian");
				weapon->move(npc);
				weapon->wield();
				break;
			case "������":
				weapon = new("/clone/weapon/changbian");
				weapon->move(npc);
				weapon->wield();
				break;
                } else {
                        string *lonelysword = ({
                                "staff",
                                "sword",
                                "hammer",
                                "club",
                                "dagger",
                                "blade",
                                "force",
                                "whip",
                                "throwing",
                                "unarmed",
                                "finger",
                                "claw",
                                "strike",
                                "hand",
                                "cuff"
                        });
                        npc->set("can_perform/lonely-sword",lonelysword);
                        npc->set("can_perform/jiuyin-baiguzhao/shenzhao",1);
                        weapon = new("/clone/weapon/changjian");
                        weapon->move(npc);
                        weapon->wield();
                }
        }

        if (npc->query("family/family_name"))
                set("long","������" + (string)npc->query("family/family_name") + "��ɱ�֡�\n");
        else
                set("long","�����ǻ���Զ��ʱ���Ĵ����񽫣�\n");

	npc->reset_action();

        return;
}

int accept_fight(object ob)
{
	object me;
	me = this_object();
        command("say �����ȥ���ɣ�");
        command("yun powerup");
        command("yun shield");
	switch (me->query_skill_mapped("force"))
	{
		case "linji-zhuang":
			command("yun tiandi");
			command("yun daxiao");
			me->set("qi",me->query("max_qi"));
			me->set("jing",me->query("max_jing"));
			break;
		case "huagong-dafa":
			command("yun hua");
			break;
		case "zixia-shengong":
			command("yun ziqi");
			break;
		case "huntian-qigong":
			command("yun haixiao");
			command("yun shengang");
			break;
		case "bibo-shengong":
			command("yun wuzhuan");
			break;
		case "yunv-xinfa":
			command("yun wang");
			break;
		case "nuhai-kuangtao":
			command("yun haixiao");
			break;
		case "xiantian-gong":
			command("yun chunyang");
			break;
		case "longxiang":
			command("yun longxiang");
			command("yun panlong");
			command("yun tunxiang");
			break;
		case "hamagong":
			command("yun reserve");
			break;
		case "lengyue-shengong":
			command("yun freeze");
			break;
		case "kurong-xinfa":
			command("yun kurong");
			break;
	}
        kill_ob(ob);
        return 1;
}

int accept_hit(object ob)
{
	object me;
	me = this_object();
        command("say �����ȥ���ɣ�");
        command("yun powerup");
        command("yun shield");
	switch (me->query_skill_mapped("force"))
	{
		case "linji-zhuang":
			command("yun tiandi");
			command("yun daxiao");
			me->set("qi",me->query("max_qi"));
			me->set("jing",me->query("max_jing"));
			break;
		case "huagong-dafa":
			command("yun hua");
			break;
		case "zixia-shengong":
			command("yun ziqi");
			break;
		case "huntian-qigong":
			command("yun haixiao");
			command("yun shengang");
			break;
		case "bibo-shengong":
			command("yun wuzhuan");
			break;
		case "yunv-xinfa":
			command("yun wang");
			break;
		case "nuhai-kuangtao":
			command("yun haixiao");
			break;
		case "xiantian-gong":
			command("yun chunyang");
			break;
		case "longxiang":
			command("yun longxiang");
			command("yun panlong");
			command("yun tunxiang");
			break;
		case "hamagong":
			command("yun reserve");
			break;
		case "lengyue-shengong":
			command("yun freeze");
			break;
		case "kurong-xinfa":
			command("yun kurong");
			break;
	}
        kill_ob(ob);
        return 1;
}

int accept_kill(object ob)
{
	object me;
	me = this_object();
        command("say �����ȥ���ɣ�");
        command("yun powerup");
        command("yun shield");
	switch (me->query_skill_mapped("force"))
	{
		case "linji-zhuang":
			command("yun tiandi");
			command("yun daxiao");
			me->set("qi",me->query("max_qi"));
			me->set("jing",me->query("max_jing"));
			break;
		case "huagong-dafa":
			command("yun hua");
			break;
		case "zixia-shengong":
			command("yun ziqi");
			break;
		case "huntian-qigong":
			command("yun haixiao");
			command("yun shengang");
			break;
		case "bibo-shengong":
			command("yun wuzhuan");
			break;
		case "yunv-xinfa":
			command("yun wang");
			break;
		case "nuhai-kuangtao":
			command("yun haixiao");
			break;
		case "xiantian-gong":
			command("yun chunyang");
			break;
		case "longxiang":
			command("yun longxiang");
			command("yun panlong");
			command("yun tunxiang");
			break;
		case "hamagong":
			command("yun reserve");
			break;
		case "lengyue-shengong":
			command("yun freeze");
			break;
		case "kurong-xinfa":
			command("yun kurong");
			break;
	}
        kill_ob(ob);
        return 1;
}

void random_move()
{
	object me,target;
	if (time() - query_temp("born_time") > 900)
	{
              remove_call_out("destruct_me");
              call_out("destruct_me",1);
	      return;
	}

        NPC_D->random_move(this_object());
}

void destruct_me()
{
	message_vision("$N����ææ�����ˡ�\n", this_object());
	destruct(this_object());
	return;
}
