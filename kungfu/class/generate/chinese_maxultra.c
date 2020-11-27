// chan_cler �й���ս��

inherit NPC;


private void from_wudang_sp();
private void from_shaolin_sp();
private void from_huashan_sp();
private void from_ouyang_sp();
private void from_gaibang_sp();
private void from_taohua_sp();
private void from_gumu_sp();
private void from_xingxiu_sp();
private void from_hu_sp();
private void from_xiaoyao_sp();
private void from_kunlun_sp();
private void from_lingxiao_sp();
private void from_tiezhang_sp();
private void from_mingjiao_sp();
private void from_murong_sp();


function *init_family = ({ 
	(: from_wudang_sp :), (: from_shaolin_sp :),	(: from_huashan_sp :), (: from_ouyang_sp :),(:from_mingjiao_sp():),
			   (: from_gaibang_sp :),(: from_taohua_sp :),	(: from_gumu_sp :),(: from_xingxiu_sp :),(: from_tiezhang_sp :),
			   (: from_hu_sp :),(: from_xiaoyao_sp :),(: from_kunlun_sp :),(: from_murong_sp :),(: from_lingxiao_sp :),});

void create()
{
        NPC_D->generate_cn_name(this_object());
        set("long", "һ���ˡ�\n");
        set("gender", "����");
        set("age", 20);
        set("str", 20);
        set("int", 13);
        set("con", 20);
        set("dex", 20);

        // the follow 5 setting has no use      
        set("max_qi", 100);
        set("max_jing", 100);
        set("neili", 100);
        set("max_neili", 100);
        set("jiali", 100);

        set("combat_exp", 3000000);

        setup();

        evaluate(init_family[random(sizeof(init_family))]);
}



private void from_wudang_sp()
{
        set("scale", 200);
        set("from", ({
                "��˵���˳����䵱�����䵱�ɵĸ��֣�Ȼ�����䲻�޵£���ϧ����ϧ��",
                "���Ŵ��˱����䵱ɽ��һũ�򣬶���ĿȾ����Ȼ���ͳɷǷ��书��",
                "��˵�������䵱��ͽ�����그��ɱ���������󣬲�����շ�����ԭ��",
        }));

        set_skill("force", 1);
        set_skill("taiji-shengong", 1);
        set_skill("parry", 1);
        set_skill("dodge", 1);
        set_skill("tiyunzong", 1);
        set_skill("sword", 1);
        set_skill("taiji-jian", 1);
        set_skill("hand", 1);
        set_skill("lonely-sword", 1);
        set_skill("unarmed", 1);
        set_skill("taiji-quan", 1);
        set_skill("literate", 1);
        set_skill("martial-cognize", 1);
        set_skill("taoism", 1);
	set_skill("count", 1);
        set_skill("shexing-lifan", 1);

        map_skill("parry", "taiji-jian");
        map_skill("force", "taiji-shengong");
        map_skill("dodge", "shexing-lifan");
        map_skill("sword", "lonely-sword");
        map_skill("hand", "paiyun-shou");
        map_skill("unarmed", "taiji-quan");

        prepare_skill("hand", "paiyun-shou");
        prepare_skill("unarmed", "taiji-quan");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
        (: perform_action, "sword.luo" :),
	(: perform_action, "sword.9in1" :),				  
        (: exert_function, "recover" :),
        }) );

        set("class", "taoist");

        carry_object("/clone/weapon/green_sword")->wield();
        carry_object("/d/wudang/obj/greyrobe")->wear();
}


private void from_shaolin_sp()
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

		set("can_perform/tianzi-jian/junlin",1);

        set_skill("force", 1);
        set_skill("yijinjing", 1);
        set_skill("parry", 1);
        set_skill("dodge", 1);
        set_skill("yiwei-dujiang", 1);
        set_skill("sword", 1);
        set_skill("tianzi-jian", 1);
        set_skill("unarmed", 1);
        set_skill("jingang-buhuaiti", 1);
        set_skill("literate", 1);
        set_skill("martial-cognize", 1);
        set_skill("buddhism", 1);
	set_skill("jiasha-fumogong", 1);
        set_skill("shexing-lifan", 1);

        map_skill("parry", "jingang-buhuaiti");
        map_skill("force", "yijinjing");
        map_skill("dodge", "shexing-lifan");
        map_skill("sword", "tianzi-jian");
        map_skill("unarmed", "jiasha-fumogong");

        prepare_skill("unarmed", "jiasha-fumogong");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
        (: perform_action, "sword.junlin" :),
        }) );

        set("class", "bonze");
        carry_object("/clone/weapon/green_sword")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

private void from_huashan_sp()
{
        set("scale", 130);
        set("from", ({
                "��˵���˳��Ի�ɽ���޶����������м���Ȼ�������벻�������ֳ�ͷ��",
                "���Ŵ��˱��ǻ�ɽ���ϣ�����֮��ԶͶ��أ���֪�ιʷ�����ԭ��",
                "��˵���˱��Ǳ����Ե׵���ɽȥ�ģ�͵ѧ�����Ժ�û�ر���"
                + "�����ٵؿ��ޣ��������ڵó�������",
        }));

        set_skill("force", 1);
        set_skill("zixia-shengong", 1);
        set_skill("parry", 1);
        set_skill("dodge", 1);
        set_skill("feiyan-huixiang", 1);
        set_skill("sword", 1);
        set_skill("huashan-sword", 1);
        set_skill("dugu-jiujian", 1);
        set_skill("cuff", 1);
        set_skill("poyu-quan", 1);
        set_skill("strike", 1);
        set_skill("lonely-sword", 1);
        set_skill("literate", 1);
        set_skill("martial-cognize", 1);
        set_skill("shexing-lifan", 1);

        map_skill("parry", "dugu-jiujian");
        map_skill("force", "zixia-shengong");
        map_skill("dodge", "shexing-lifan");
        map_skill("sword", "lonely-sword");
        map_skill("cuff", "poyu-quan");
        map_skill("strike", "hunyuan-zhang");

        prepare_skill("cuff", "poyu-quan");
        prepare_skill("strike", "hunyuan-zhang");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
        (: perform_action, "sword.luo" :),
	(: perform_action, "sword.9in1" :),	
        (: exert_function, "recover" :),
        }) );

        set("class", "fighter");

        carry_object("/clone/weapon/green_sword")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

private void from_ouyang_sp()
{
        set("scale", 130);
        set("from", ({
                "��˵����ԭ����ɽͯ�ѵ��ֳ�����֪�ι�ʧ�٣���"
                + "�վ�Ȼ�ֳ����ˡ�",
                "���Ŵ���͵ѧ�����չ���ɽͯ�ѵ��书����������ɽ"
                + "ͯ�ѷ��ִ�����ˣ����˴��˶��ߣ���Ȼ����գ�����˼�飡",
        }));

        set_skill("force", 1);
        set_skill("jiuyin-shengong", 1);
        set_skill("bahuang-gong", 1);
        set_skill("zhemei-shou", 1);
        set_skill("hand", 1);
        set_skill("parry", 1);
        set_skill("dodge", 1);
        set_skill("qiankun-danuoyi", 1);
        set_skill("staff", 1);
        set_skill("lingshe-zhangfa", 1);
        set_skill("cuff", 1);
        set_skill("lingshe-quan", 1);
        set_skill("unarmed", 1);
        set_skill("dafumo-quan", 1);
        set_skill("literate", 1);
        set_skill("martial-cognize", 1);
        set_skill("shexing-lifan", 1);
        set_skill("qimen-wuxing", 1);
	set_skill("zuoyou-hubo", 1);

        map_skill("force", "bahuang-gong");
        map_skill("parry", "qiankun-danuoyi");
        map_skill("dodge", "shexing-lifan");
        map_skill("unarmed", "jiuyin-shengong");
        map_skill("hand", "zhemei-shou");


        prepare_skill("hand", "zhemei-shou");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
	(: command("perform hand.tanmei twice") :),
        (: exert_function, "recover" :),
        }) );

        carry_object("/clone/cloth/cloth")->wear();
}

private void from_gaibang_sp()
{
        set("scale", 120);
        set("from", ({
                "��˵����ԭ��ؤ�ﳤ�ϣ��书�߾���������������Ů�Ӷ���"
                + "������⣬�������ֽ�����������Ѫ���ȷ硣"
        }));

        set_skill("force", 1);
        set_skill("huntian-qigong", 1);
        set_skill("parry", 1);
        set_skill("dodge", 1);
        set_skill("feiyan-zoubi", 1);
        set_skill("staff", 1);
        set_skill("qiankun-danuoyi", 1);
        set_skill("strike", 1);
        set_skill("xianglong-zhang", 1);
        set_skill("literate", 1);
        set_skill("martial-cognize", 1);
        set_skill("shexing-lifan", 1);
	set_skill("zuoyou-hubo", 1);

        map_skill("force", "huntian-qigong");
        map_skill("parry", "qiankun-danuoyi");
        map_skill("dodge", "shexing-lifan");
        map_skill("staff", "dagou-bang");
        map_skill("strike", "xianglong-zhang");

        prepare_skill("strike", "xianglong-zhang");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
	(: command("perform strike.3hui twice") :),
        (: exert_function, "recover" :),
        }) );

        set("class", "begger");
   
        carry_object("/clone/cloth/cloth")->wear();
}


private void from_taohua_sp()
{
        object ob;

        set("scale", 135);
        set("from", ({
                "��˵���˺��һ�������ҩʦ��Щ��ϵ��",
        }));

        set_skill("force", 1);
        set_skill("bibo-shengong", 1);
	set_skill("bihai-chaosheng", 1);
	set_skill("dodge", 1);
        set_skill("anying-fuxiang", 1);
        set_skill("finger", 1);
        set_skill("throwing", 1);
        set_skill("tanzhi-shentong", 1);
        set_skill("parry", 1);
        set_skill("sword", 1);
        set_skill("never-defeated", 1);
        set_skill("qimen-wuxing", 1);
        set_skill("jingluo-xue", 1);
        set_skill("mathematics", 1);
        set_skill("literate", 1);
        set_skill("martial-cognize", 1);
        set_skill("shexing-lifan", 1);

        map_skill("force", "never-defeated");
        map_skill("finger", "tanzhi-shentong");
        map_skill("dodge", "shexing-lifan");
        map_skill("parry", "never-defeated");
        map_skill("sword", "never-defeated");
        map_skill("throwing", "tanzhi-shentong");

        prepare_skill("finger" , "tanzhi-shentong");

        set("chat_chance_combat", 180);
	set("chat_msg_combat", ({
	(: perform_action, "sword.wanli" :),
	(: exert_function, "powerup" :),
	(: exert_function, "recover" :),
	}));
        carry_object("/clone/weapon/green_sword")->wield();
        carry_object("/clone/misc/cloth")->wear();
        ob = carry_object("/d/taohua/obj/huaban");
        ob->set_amount(80);
        set_temp("handing", ob);
}


private void from_gumu_sp()
{
        object ob;

        set("scale", 130);
        set("from", ({
                "��˵�����ǻ��ӹ��ĵ��ӣ��������ʦ���ˡ�",
                "���˾�˵��÷ׯ���ˣ��ͺڰ�������ԨԴ��",
        }));

        set_skill("force", 1);
        set_skill("xuantian-wujigong", 1);
        set_skill("parry", 1);
        set_skill("dodge", 1);
        set_skill("zhuangzi-wu", 1);
        set_skill("unarmed", 1);
        set_skill("qixian-wuxingjian", 1);
        set_skill("strike", 1);
        set_skill("qiankun-danuoyi", 1);
        set_skill("tianluo-diwang", 1);
        set_skill("throwing", 1);
        set_skill("yufeng-zhen", 1);
        set_skill("sword", 1);
        set_skill("yunv-jian", 1);
        set_skill("quanzhen-jian", 1);
        set_skill("tanqin-jifa", 1);
        set_skill("literate", 1);
        set_skill("martial-cognize", 1);
	set_skill("zuoyou-hubo", 1);

        map_skill("force", "xuantian-wujigong");
        map_skill("sword", "qixian-wuxingjian");
        map_skill("dodge", "zhuangzi-wu");
        map_skill("parry", "qiankun-danuoyi");
        map_skill("unarmed", "qixian-wuxingjian");
        map_skill("strike", "tianluo-diwang");
        map_skill("throwing", "yufeng-zhen");

        prepare_skill("unarmed", "qixian-wuxingjian");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({    
	(: command("perform bayin") :),
        }) );

        carry_object("/clone/weapon/green_sword")->wield();
        carry_object("/clone/misc/cloth")->wear();
        ob = carry_object("/d/gumu/obj/yufeng-zhen");
        ob->set_amount(30);
        set_temp("handing", ob);
}

private void from_xingxiu_sp()
{
        set("scale", 130);
		set("reburn", 1);
        set("from", ({
                "��˵�����������ɵ��ӣ���Ϊ���������ɣ�ֻ���ӳ������ɡ�",
        }));

        set_skill("force", 1);
        set_skill("kuihua-mogong", 1);
        set_skill("dodge", 1);
        set_skill("zhaixinggong", 1);
        set_skill("strike", 1);
        set_skill("chousui-zhang", 1);
        set_skill("claw", 1);
        set_skill("sanyin-wugongzhao", 1);
        set_skill("whip", 1);
        set_skill("chanhun-suo", 1);
        set_skill("parry", 1);
        set_skill("staff", 1);
        set_skill("tianshan-zhang", 1);
        set_skill("throwing", 1);
        set_skill("feixing-shu", 1);
        set_skill("unarmed", 1);
        set_skill("xingxiu-qishu", 1);
        set_skill("literate", 1);
        set_skill("martial-cognize", 1);

        map_skill("force", "kuihua-mogong");
        map_skill("dodge", "kuihua-mogong");
        map_skill("unarmed", "kuihua-mogong");
	map_skill("sword", "kuihua-mogong");
        map_skill("claw", "sanyin-wugongzhao");
        map_skill("whip", "chanhun-suo");
        map_skill("parry", "kuihua-mogong");
        map_skill("staff", "tianshan-zhang");
        map_skill("poison", "xingxiu-qishu");

        prepare_skill("unarmed", "kuihua-mogong");


        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
        (: perform_action, "sword.bian" :),
        (: perform_action, "sword.dongfang" :),
        }));

        carry_object("/clone/weapon/green_sword")->wield();
        carry_object("/clone/misc/cloth")->wear();
}


private void from_hu_sp()
{
        object ob;
        set("scale", 135);
		set("reburn", 1);
        set("from", ({
                "��˵���˺�����ѩɽ�ɺ���˵����Ĺ�ϵ��",
        }));

        set_skill("force", 1);
        set_skill("lengyue-shengong", 1);
        set_skill("blade", 1);
        set_skill("dodge", 1);
        set_skill("sword", 1);
        set_skill("qiankun-danuoyi", 1);
        set_skill("zhuangzi-wu", 1);
        set_skill("cuff", 1);
        set_skill("daojian-guizhen", 1);
        set_skill("parry", 1);
        set_skill("lamaism", 1);
        set_skill("literate", 1);
        set_skill("martial-cognize", 1);

        map_skill("force", "lengyue-shengong");
        map_skill("dodge", "zhuangzi-wu");
        map_skill("parry", "qiankun-danuoyi");
        map_skill("blade", "daojian-guizhen");
	map_skill("sword", "daojian-guizhen");


        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
        (: perform_action, "blade.wai" :),
        (: exert_function, "recover" :),
        }));

        set("class", "bonze");

        carry_object("/clone/weapon/tudao")->wield();
        carry_object("/clone/misc/cloth")->wear();		      
	ob = carry_object("/clone/weapon/green_sword");       
        set_temp("handing", ob);
}


private void from_xiaoyao_sp()
{
        set("scale", 135);
        set("from", ({
                "��˵���˺ͺ�ɽ��Ī����ͬ�ŵ��ӣ�������֪�ιʷ����ɳ�",
        }));

        set_skill("force", 1);
        set_skill("zhenyue-jue", 1);
        set_skill("dodge", 1);
        set_skill("lingbo-weibu", 1);
        set_skill("liuyang-zhang", 1);
        set_skill("parry", 1);
        set_skill("sword", 1);
        set_skill("wuyue-shenjian", 1);
        set_skill("zhemei-shou", 1);
        set_skill("hand", 1);
	set_skill("finger", 1);
	set_skill("liumai-shenjian", 1);
        set_skill("strike", 1);
        set_skill("literate", 1);
	set_skill("zuoyou-hubo", 1);
        set_skill("martial-cognize", 1);
	set_skill("qiankun-danuoyi", 1);

        map_skill("force", "zhenyue-jue");
        map_skill("dodge", "lingbo-weibu");
        map_skill("sword", "wuyue-shenjian");
        map_skill("finger", "liumai-shenjian");
        map_skill("strike", "liuyang-zhang");
        map_skill("parry", "qiankun-danuoyi");

        prepare_skill("finger","liumai-shenjian");


        set("class", "taoist");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
        (: command("perform sword.shen twice") :),
        }));

        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/green_sword")->wield();
}


private void from_kunlun_sp()
{
        set("scale", 135);
        set("from", ({
                "�����������죬��ͬ��һ���������ϣ���˵��������������ԨԴ��",
        }));

        set_skill("force", 1);
        set_skill("liangyi-shengong", 1);
        set_skill("dodge", 1);
        set_skill("zhuangzi-wu", 1);
        set_skill("strike", 1);
        set_skill("tanqin-jifa", 1);
	set_skill("chess", 1);
        set_skill("cuff", 1);
        set_skill("zhentian-quan", 1);
        set_skill("parry", 1);
        set_skill("sword", 1);
        set_skill("daya-jian", 1);
        set_skill("qiankun-jian", 1);
        set_skill("jian-jia", 1);
        set_skill("martial-cognize", 1);
        set_skill("qiankun-danuoyi", 1);

        map_skill("force", "liangyi-shengong");
        map_skill("dodge", "zhuangzi-wu");
        map_skill("parry", "qiankun-danuoyi");
        map_skill("sword", "daya-jian");
        map_skill("tanqin-jifa", "jian-jia");

        prepare_skill("cuff", "zhentian-quan");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
        (: perform_action, "sword.bugui" :),
        }));

        carry_object("/clone/weapon/green_sword")->wield();
        carry_object("/clone/misc/cloth")->wear();
}



private void from_lingxiao_sp()
{
        set("scale", 140);
		set("reburn", 1);
		set("can_perform/xueshan-jian/times", 1600000);
        set("from", ({
                "�����˴�ѩɽ�����Ǹ��֣����������±䣬�����ɶ�ȥ��",
        }));

        set_skill("force", 1);
        set_skill("taixuan-gong", 1);
        set_skill("dodge", 1);
        set_skill("qiankun-danuoyi", 1);
        set_skill("unarmed", 1);
        set_skill("lingxiao-quan", 1);
        set_skill("zhuangzi-wu", 1);
        set_skill("piaoxu-zhang", 1);
        set_skill("sword", 1);
        set_skill("shangqing-jian", 1);
        set_skill("parry", 1);
        set_skill("zuoyou-hubo", 1);
		set_skill("xueshan-jian", 1);
		set_skill("shangqing-jian", 1);
        set_skill("martial-cognize", 1);

        map_skill("force", "taixuan-gong");
        map_skill("dodge", "zhuangzi-wu");
        map_skill("unarmed", "taixuan-gong");
        map_skill("strike", "piaoxu-zhang");
        map_skill("sword", "xueshan-jian");
        map_skill("parry", "qiankun-danuoyi");

        prepare_skill("unarmed", "taixuan-gong");


        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
        (: command("perform sword.chu twice") :),
		(: command("perform sword.feng") :),
        }));

        carry_object("/clone/weapon/green_sword")->wield();
        carry_object("/clone/misc/cloth")->wear();
}

private void from_tiezhang_sp()
{
        object ob;
        set("scale", 120);
		set("reburn", 1);
        set("from", ({
                "�����˾���ȸ��֣��ܹ���ֹ֮�г������¡�",
        }));

        set_skill("force", 1);
        set_skill("tianlei-shengong", 1);
        set_skill("dodge", 1);
        set_skill("dengping-dushui", 1);
        set_skill("strike", 1);
        set_skill("parry", 1);
        set_skill("tie-zhang", 1);
        set_skill("feilong-zhang", 1);
        set_skill("yinyang-ren", 1);
        set_skill("hand", 1);
        set_skill("sword", 1);
        set_skill("blade", 1);
	set_skill("qiankun-danuoyi", 1);		
        set_skill("literate", 1);
        set_skill("zuoyou-hubo", 1);
        set_skill("martial-cognize", 1);

        map_skill("force", "tianlei-shengong");
        map_skill("strike", "tie-zhang");
        map_skill("parry", "qiankun-danuoyi");
        map_skill("dodge", "dengping-dushui");
        map_skill("staff", "feilong-zhang");
        map_skill("sword", "yinyang-ren");
        map_skill("blade", "yinyang-ren");

        prepare_skill("strike", "tie-zhang");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
        (: command("perform blade.jqjy twice") :),
        }));

        carry_object("/clone/weapon/tudao")->wield();
        carry_object("/clone/misc/cloth")->wear();		      
	ob = carry_object("/clone/weapon/green_sword");       
        set_temp("handing", ob);
}


private void from_mingjiao_sp()
{
        set("scale", 120);
        set("from", ({
                "���˸����̽�����������˵����������Ĺ�ϵ��",
        }));

        set_skill("force", 1);
        set_skill("jiuyang-shengong", 1);
        set_skill("dodge", 1);
        set_skill("qingfu-shenfa", 1);
	set_skill("qiankun-danuoyi", 1);
        set_skill("unarmed", 1);
        set_skill("parry", 1);
        set_skill("literate", 1);
        set_skill("martial-cognize", 1);

        map_skill("force", "jiuyang-shengong");
        map_skill("unarmed", "jiuyang-shengong");
        map_skill("parry", "qiankun-danuoyi");
        map_skill("dodge", "qingfu-shenfa");


        prepare_skill("unarmed", "jiuyang-shengong");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
        (: perform_action, "unarmed.ri" :),

        }));

        carry_object("/clone/misc/cloth")->wear();
}



private void from_murong_sp()
{
        set("scale", 120);
        set("from", ({
                "���˸�Ľ��������˵����������Ĺ�ϵ��",
        }));

        set_skill("force", 1);
        set_skill("zihui-xinfa", 1);
        set_skill("dodge", 1);
        set_skill("shexing-lifan", 1);
	set_skill("douzhuan-xingyi", 1);
        set_skill("finger", 1);
        set_skill("parry", 1);
        set_skill("literate", 1);
        set_skill("martial-cognize", 1);
	set_skill("canhe-zhi", 1);
	set_skill("jingluo-xue", 1);
	set_skill("yiyang-zhi", 1);
	set_skill("lamaism", 1);
	set_skill("buddhism", 1);

        map_skill("force", "zihui-xinfa");
        map_skill("finger", "canhe-zhi");
        map_skill("parry", "douzhuan-xingyi");
        map_skill("dodge", "shexing-lifan");


        prepare_skill("finger", "canhe-zhi");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
        (: perform_action, "finger.mieshi" :),

        }));

        carry_object("/clone/misc/cloth")->wear();
}