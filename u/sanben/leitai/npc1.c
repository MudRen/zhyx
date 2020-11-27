
//��̨npc1

#include <ansi.h> 
inherit  __DIR__"leitai_npc";
void do_disappear();
void create()
{           
        set("level", 1);        
        set("name", "��ҩʦ");
        set("id", "huang yaoshi");       
       
        set("title", "�����һ�������");
        set("nickname", HIC "��а" NOR );
        set("gender", "����");
        set("age", 42);
        set("long", "�������һ����������ºö�ȫ�ɼ��ģ���˱�\n"
                    "�˳�������а����\n");
        set("attitude", "peaceful");
        set("class", "scholar");
        set("str", 50);
        set("int", 50);
        set("con", 50);
        set("dex", 50);
        set("qi", 10000);
        set("max_qi", 10000);
        set("jing", 5000);
        set("max_jing", 5000);
        set("neili", 20000);
        set("max_neili", 20000);
        set("jiali", 300);
        set("combat_exp", 3000000);

        set_skill("force", 300);
        set_skill("bibo-shengong", 300);
        set_skill("luoying-xinfa", 300);
        set_skill("hand", 300);
        set_skill("finger", 300);
        set_skill("canglang-zhi", 300);
        set_skill("tanzhi-shentong", 300);
        set_skill("unarmed", 300);
        set_skill("strike", 300);
        set_skill("pikong-zhang", 300);
        set_skill("luoying-shenzhang", 300);
        set_skill("xuanfeng-tui", 300);
        set_skill("dodge", 300);
        set_skill("anying-fuxiang", 300);
        set_skill("parry", 300);
        set_skill("sword", 300);
        set_skill("throwing", 300);
        set_skill("luoying-shenjian", 300);
        set_skill("yuxiao-jian", 300);
        set_skill("lanhua-shou", 300);
        set_skill("qimen-wuxing", 300);
        set_skill("count", 300);
        set_skill("jingluo-xue", 300);
        set_skill("mathematics", 300);
        set_skill("literate", 300);
        set_skill("chuixiao-jifa", 300);
        set_skill("bihai-chaosheng", 300);
        set_skill("taohua-yuan", 300);
        set_skill("drawing", 300);
        set_skill("chess", 300);
        set_skill("calligraphy", 300);
        set_skill("medical", 300);
        set_skill("taohua-yaoli", 300);
        set_skill("martial-cognize", 300);

        map_skill("force", "bibo-shengong");
        map_skill("finger", "tanzhi-shentong");
        map_skill("hand", "lanhua-shou");
        map_skill("unarmed", "xuanfeng-tui");
        map_skill("strike", "luoying-shenzhang");
        map_skill("dodge", "anying-fuxiang");
        map_skill("parry", "tanzhi-shentong");
        map_skill("sword", "yuxiao-jian");
        map_skill("chuixiao-jifa", "bihai-chaosheng");
        map_skill("throwing", "tanzhi-shentong");
        map_skill("medical", "taohua-yaoli");

        prepare_skill("finger" , "tanzhi-shentong");

        create_family("�һ���", 1, "����");
   
        // npc��pfm
        set("pfm", ({
             "sword.bihai", 
             "sword.qing",
             "sword.tian", 
             "finger.ding", 
             "finger.zhuan",
             "finger.zhuan",              
         }));
        //npc�ı���
        set("weapon","/clone/weapon/changjian"); 

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




