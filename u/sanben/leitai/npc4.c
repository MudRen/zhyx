
//��̨npc4

#include <ansi.h> 
inherit  __DIR__"leitai_npc";
void do_disappear();
void create()
{           
        set("level", 4);        
        set("name", "���߹�");
        set("id", "hong qigong");       
       
        set("long", @LONG
������ؤ���ʮ���ΰ������ųƾ�ָ��ؤ�ĺ�
�߹���ү�ӡ�ֻ������ü�԰ף�������������
���ѣ�ģ������������������Ŀ����磬�Ե�
������Ȼ����ŭ��������
LONG);
        set("nickname", HIW "��ؤ" NOR);
        set("gender", "����");
        set("class", "beggar");
        set("age", 75);
        set("attitude", "peaceful");

        set("str", 50);
        set("int", 50);
        set("con", 50);
        set("dex", 50);
        set("max_qi", 18000);
        set("max_jing", 8000);
        set("neili", 20000);
        set("max_neili", 20000);
        set("jiali", 450);
        set("combat_exp", 10000000);
        set("score", 400000);
        set("shen_type", 1);

        set_skill("force", 450);
        set_skill("jiaohua-neigong", 450);
        set_skill("huntian-qigong", 450);
        set_skill("yijin-duangu", 450);
        set_skill("dodge", 450);
        set_skill("feiyan-zoubi", 450);
        set_skill("xiaoyaoyou", 450);
        set_skill("unarmed", 450);
        set_skill("changquan", 450);
        set_skill("jueming-tui", 450);
        set_skill("hand", 450);
        set_skill("chansi-shou", 450);
        set_skill("claw", 450);
        set_skill("suohou-gong", 450);
        set_skill("strike", 450);
        set_skill("xianglong-zhang", 450);
        set_skill("tongchui-zhang", 450);
        set_skill("liuhe-zhang", 450);
        set_skill("parry", 450);
        set_skill("staff", 450);
        set_skill("dagou-bang", 450);
        set_skill("jiaohua-bangfa", 450);
        set_skill("fengmo-zhang", 450);
        set_skill("fumo-zhang", 450);
        set_skill("throwing", 450);
        set_skill("pomie-jinzhen", 450);
        set_skill("begging", 450);
        set_skill("checking", 450);
        set_skill("literate", 450);
        set_skill("martial-cognize", 450);

        map_skill("throwing", "pomie-jinzhen");
        map_skill("force", "huntian-qigong");
        map_skill("unarmed", "changquan");
        map_skill("hand", "chansi-shou");
        map_skill("claw", "suohou-gong");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("parry", "dagou-bang");
        map_skill("staff", "dagou-bang");
        map_skill("strike", "xianglong-zhang");

        prepare_skill("strike", "xianglong-zhang");

        create_family("ؤ��", 17, "����");

        // npc��pfm
        set("pfm", ({
             "strike.qu", 
             "strike.zhen",
             "strike.fei", 
             "unarmed.jian", 
             "dodge.xian",         
         }));
        //npc�ı���
        set("hand","/d/city/npc/obj/tieshou"); 


       //�������ݲ���
        set("chat_chance", 200);
        set("chat_msg", ({ 
                      (: do_disappear :),                       
        }));
        set("chat_chance_combat", 200);
	 set("chat_msg_combat", ({	
           (: pfm : ),
           (: exert_function, "recover" :),        
	  }) );   
        
        restore();
        setup();  
        if (clonep()) keep_heart_beat();         
        carry_object("/d/city/npc/obj/jinsijia")->wear();        
        if ( query("weapon") )
            carry_object(query("weapon"))->wield(); 
        if ( query("hand") )
            carry_object(query("hand"))->wear();       
           
}




