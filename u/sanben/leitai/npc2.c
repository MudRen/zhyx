
//擂台npc2

#include <ansi.h> 
inherit  __DIR__"leitai_npc";
void do_disappear();
void create()
{           
        set("level", 2);        
        set("name", "欧阳锋");
        set("id", "ouyang feng");     
     
        set("long", "他就是白驼山庄主，号称“西毒”的欧阳锋。脸型瘦削，\n"
                    "身形剽悍，虽然受到郭靖欺骗误学习了「九阴真经」而走\n"
                    "火入魔，一度变得精神错乱，但是现在已然恢复，功力犹\n"
                    "胜往昔。\n");
        set("title", "西域白驼山庄主");
        set("gender", "男性");
        set("age", 53);
        set("nickname", HIR "西毒" NOR);
        set("shen_type", -1);
        set("attitude", "peaceful");

        set("str", 50);
        set("int", 50);
        set("con", 50);
        set("dex", 50);

        set("qi", 12000);
        set("max_qi", 12000);
        set("jing", 5000);
        set("max_jing", 5000);
        set("neili", 20000);
        set("max_neili", 20000);
        set("jiali", 350);

        set("combat_exp", 5000000);

        set_skill("force", 350);
        set_skill("unarmed", 350);
        set_skill("baituo-xinfa", 350);

        set_skill("dodge", 350);
        set_skill("parry", 350);
        set_skill("cuff", 350);
        set_skill("finger", 350);
        set_skill("staff", 350);
        set_skill("training", 350);
        set_skill("poison", 350);
        set_skill("shedu-qiqiao", 350);
        set_skill("hamagong", 350);
        set_skill("chanchu-bufa", 350);
        set_skill("lingshe-quan", 350);
        set_skill("lingshe-zhangfa", 350);
        set_skill("baibian-daxue", 350);
        set_skill("guzheng-jifa", 350);
        set_skill("xiyu-tiezheng", 350);
        set_skill("wushe-qu", 350);
        set_skill("literate", 350);
        set_skill("medical", 350);
        set_skill("baituo-michuan", 350);
        set_skill("martial-cognize", 350);

        map_skill("force", "hamagong");
        map_skill("dodge", "chanchu-bufa");
        map_skill("cuff", "lingshe-quan");
        map_skill("parry", "lingshe-zhangfa");
        map_skill("staff", "lingshe-zhangfa");
        map_skill("finger", "shedu-qiqiao");
        map_skill("poison", "shedu-qiqiao");
        map_skill("medical", "baituo-michuan");
        map_skill("guzheng-jifa", "xiyu-tiezheng");

        prepare_skill("finger", "shedu-qiqiao");
        prepare_skill("cuff", "lingshe-quan");

        create_family("欧阳世家", 5, "掌门");
   
        // npc的pfm
        set("pfm", ({
             "staff.chan", 
             "staff.qianshe",
             "staff.wuji", 
             "cuff.rou",              
         }));
        //npc的兵器
        set("weapon","/d/baituo/obj/tiezheng"); 

       //以下数据不变
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




