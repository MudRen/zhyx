// chan_cler �й���ս��

inherit NPC;

private void from_wudang();
private void from_shaolin();
private void from_huashan();
private void from_ouyang();
private void from_gaibang();
void random_move();
void destruct_me();
int  is_stay_in_room();

function *init_family = ({ (: from_wudang :), (: from_shaolin :), (: from_huashan :),
                           (: from_ouyang :), (: from_gaibang :) });

void create()
{
       set_name("�й���", ({ "chinese" }));
	set("long", "һ���ˡ�\n");
	set("gender", "����");
	set("age", 20);
	set("str", 20);
	set("int", 20);
	set("con", 20);
	set("dex", 20);

        // the follow 5 setting has no use	
	set("max_qi", 100);
	set("max_jing", 100);
	set("neili", 100);
	set("max_neili", 100);
	set("jiali", 100);

	set("combat_exp", 3000000);

	set_skill("force", 1);
	set_skill("dodge", 1);
	set_skill("parry", 1);

       set("chat_chance", 30);
       set("chat_msg", ({ (: random_move :) }));
       set("scale", 100);
	set_temp("born_time", time());
        add_money("silver",50);
       keep_heart_beat();
	setup();

       evaluate(init_family[random(sizeof(init_family))]);
}

private void from_wudang()
{
        set("scale", 200);
        set("from", ({
                "��˵���˳����䵱�����䵱�ɵĸ��֣�Ȼ�����䲻�޵£���ϧ����ϧ��",
                "���Ŵ��˱����䵱ɽ��һũ�򣬶���ĿȾ����Ȼ���ͳɷǷ��书��",
                "��˵�������䵱��ͽ�����그��ɱ���������󣬲�����շ�����ԭ��",
        }));

        set_skill("taiji-shengong", 1);
        set_skill("parry", "taiji-jian");
        set_skill("tiyunzong", 1);
        set_skill("sword", 1);
        set_skill("taiji-jian", 1);
        set_skill("hand", 1);
        set_skill("paiyun-shou", 1);
        set_skill("unarmed", 1);
        set_skill("taiji-quan", 1);

        map_skill("force", "taiji-shengong");
        map_skill("dodge", "tiyunzong");
        map_skill("sword", "taiji-jian");
        map_skill("hand", "paiyun-shou");
        map_skill("unarmed", "taiji-quan");

        prepare_skill("hand", "paiyun-shou");
        prepare_skill("unarmed", "taiji-quan");

	set("chat_chance_combat", 60);
	set("chat_msg_combat", ({
		(: exert_function, "powerup" :),
		(: perform_action, "sword.lian" :),
		(: perform_action, "unarmed.zhen" :),
		(: exert_function, "recover" :),
	}) );

        carry_object("/clone/weapon/changjian")->wield();
	carry_object("/d/wudang/obj/greyrobe")->wear();
}

private void from_shaolin()
{
        set("scale", 150);
        set("from", ({
                "��˵���˳������֣������ֵ��׼Ҹ��֣���ȴû�а��ȱ�֮�ģ�����",
                "���Ŵ���͵ʦ�����֣�������һ�������׵ı��졣",
                "��˵���������ֵĻ�ͷ�ӣ�͵ѧ���պ󱻷��֣���Ȼ����"
                + "��ĦԺ���ϳ��������벻�����շ�����ԭ��",
                "��˵���˵��그�����ֵĽ��ɣ��������£��벻�����Ӷ���"
                + "�Ժ��Ȼ�س�������"
        }));

        set_skill("hunyuan-yiqi", 1);
        set_skill("parry", "damo-jian");
        set_skill("shaolin-shenfa", 1);
        set_skill("sword", 1);
        set_skill("damo-jian", 1);
        set_skill("finger", 1);
        set_skill("nianhua-zhi", 1);
        set_skill("strike", 1);
        set_skill("sanhua-zhang", 1);

        map_skill("force", "hunyuan-yiqi");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("sword", "damo-jian");
        map_skill("finger", "nianhua-zhi");
        map_skill("strike", "sanhua-zhang");

        prepare_skill("finger", "nianhua-zhi");
        prepare_skill("strike", "sanhua-zhang");

	set("chat_chance_combat", 100);
	set("chat_msg_combat", ({
		(: perform_action, "sword.sanjue" :),
		(: perform_action, "strike.san" :),
		(: exert_function, "powerup" :),
		(: exert_function, "recover" :),
		(: exert_function, "recover" :),
	}) );

        carry_object("/clone/weapon/changjian")->wield();
	carry_object("/clone/cloth/cloth")->wear();
}

private void from_huashan()
{
        set("scale", 130);
        set("from", ({
                "��˵���˳��Ի�ɽ���޶����������м���Ȼ�������벻�������ֳ�ͷ��",
                "���Ŵ��˱��ǻ�ɽ���ϣ�����֮��ԶͶ��أ���֪�ιʷ�����ԭ��",
                "��˵���˱��Ǳ����Ե׵���ɽȥ�ģ�͵ѧ�����Ժ�û�ر���"
                + "�����ٵؿ��ޣ��������ڵó�������",
        }));

        set_skill("zixia-shengong", 1);
        set_skill("parry", "huashan-sword");
        set_skill("feiyan-huixiang", 1);
        set_skill("sword", 1);
        set_skill("huashan-sword", 1);
        set_skill("cuff", 1);
        set_skill("poyu-quan", 1);
        set_skill("strike", 1);
        set_skill("hunyuan-zhang", 1);

        map_skill("force", "zixia-shengong");
        map_skill("dodge", "feiyan-huixiang");
        map_skill("sword", "huashan-sword");
        map_skill("cuff", "poyu-quan");
        map_skill("strike", "hunyuan-zhang");

        prepare_skill("cuff", "poyu-quan");
        prepare_skill("strike", "hunyuan-zhang");

	set("chat_chance_combat", 100);
	set("chat_msg_combat", ({
		(: perform_action, "sword.jianzhang" :),
		(: perform_action, "cuff.leidong" :),
		(: perform_action, "cuff.poshi" :),
		(: exert_function, "powerup" :),
		(: exert_function, "recover" :),
		(: exert_function, "recover" :),
	}) );

        carry_object("/clone/weapon/changjian")->wield();
	carry_object("/clone/cloth/cloth")->wear();
}

private void from_ouyang()
{
        set("scale", 130);
        set("from", ({
                "��˵����ԭ�ǵ���������ʦŷ������ֳ�����֪�ι�ʧ�٣���"
                + "�վ�Ȼ�ֳ����ˡ�",
                "���Ŵ���͵ѧ���������ɽׯŷ�����ҵ��书��������ŷ��"
                + "�淢�ִ�����ˣ����˴��˶��ߣ���Ȼ����գ�����˼�飡",
        }));

        set_skill("hamagong", 1);
        set_skill("chanchu-bufa", 1);
        set_skill("staff", 1);
        set_skill("lingshe-zhangfa", 1);
        set_skill("cuff", 1);
        set_skill("lingshe-quan", 1);
        set_skill("finger", 1);
        set_skill("shedu-qiqiao", 1);

        map_skill("force", "hamagong");
        map_skill("parry", "lingshe-zhangfa");
        map_skill("dodge", "chanchu-bufa");
        map_skill("staff", "lingshe-zhangfa");
        map_skill("cuff", "lingshe-quan");
        map_skill("finger", "shedu-qiqiao");

        prepare_skill("cuff", "lingshe-quan");
        prepare_skill("finger", "shedu-qiqiao");

	set("chat_chance_combat", 100);
	set("chat_msg_combat", ({
		(: perform_action, "staff.lingshe" :),
		(: exert_function, "powerup" :),
		(: exert_function, "recover" :),
		(: exert_function, "recover" :),
	}) );

        carry_object("/clone/weapon/gangzhang")->wield();
	carry_object("/clone/cloth/cloth")->wear();
}

private void from_gaibang()
{
        set("scale", 130);
        set("from", ({
                "��˵����ԭ��ؤ�ﳤ�ϣ��书�߾���������������Ů�Ӷ���"
                + "������⣬�������ֽ�����������Ѫ���ȷ硣"
        }));

        set_skill("huntian-qigong", 1);
        set_skill("feiyan-zoubi", 1);
        set_skill("staff", 1);
        set_skill("dagou-bang", 1);
        set_skill("strike", 1);
        set_skill("dragon-strike", 1);

        map_skill("force", "huntian-qigong");
        map_skill("parry", "dagou-bang");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("staff", "dagou-bang");
        map_skill("strike", "dragon-strike");

        prepare_skill("strike", "dragon-strike");

	set("chat_chance_combat", 100);
	set("chat_msg_combat", ({
		(: exert_function, "powerup" :),
		(: exert_function, "recover" :),
		(: exert_function, "recover" :),
	}) );

       carry_object("/clone/weapon/gangzhang")->wield();
	carry_object("/clone/cloth/cloth")->wear();
}

int accept_fight(object ob)
{
        command("say �ܺã����ҾͲ������ˡ�");
        kill_ob(ob);
        return 1;
}

int accept_hit(object ob)
{
        command("say �ߣ�ʲô�ˣ�");
        kill_ob(ob);
        return 1;
}

void random_move()
{
	if (time() - query_temp("born_time") > 600)
	{
		destruct_me();
		return;
	}
       GROUP_QUEST_D->random_move(this_object());
}

void destruct_me()
{
        message_vision("$N����ææ�����ˡ�\n", this_object());
        destruct(this_object());
}
