
//擂台npc5

#include <ansi.h> 
inherit  __DIR__"leitai_npc";
void do_disappear();
void create()
{           
        set("level", 5);        
        set("name", "王重阳");
        set("id", "wang chongyang");
        set("long", @LONG
他就是全真教的开山祖师、首代掌教王重阳王
真人。他白须飘飘，宽袍缓袖，眉目清癯，颇
有些仙风道骨的味道。他本来一腔热血欲报效
国家力抗金兵，可惜朝廷腐败，于是便心灰意
冷，兼此时又从道德经中悟得了天地万物滋生
的大道，从而手创全真教。
LONG);
        set("title", "全真派开山祖师");
        set("nickname", HIW "中神通" NOR);
        set("age", 76);
        set("gender", "男性");
        set("class", "taoist");
        set("attitude", "peaceful");
        set("shen_type", 1);

        set("str", 50);
        set("int", 50);
        set("con", 50);
        set("dex", 50);
        set("max_qi", 20000);
        set("max_jing", 10000);
        set("neili", 30000);
        set("jingli", 10000);
        set("max_neili", 30000);
        set("max_jingli", 10000);
        set("jiali", 500);
        set("combat_exp", 15000000);
        set("score", 500000);

       
        set_skill("force", 500);
        set_skill("quanzhen-xinfa", 500);
        set_skill("xuanmen-neigong", 500);
        set_skill("unarmed", 500);
        set_skill("xiantian-gong", 500);
        set_skill("dodge", 500);
        set_skill("tianshan-feidu", 500);
        set_skill("jinyan-gong", 500);
        set_skill("parry", 500);
        set_skill("jinguan-yusuo", 500);
        set_skill("strike", 500);
        set_skill("chongyang-shenzhang", 500);
        set_skill("haotian-zhang", 500);
        set_skill("finger", 500);
        set_skill("zhongnan-zhi", 500);
        set_skill("yiyang-zhi", 500);
        set_skill("hand", 500);
        set_skill("qixing-shou", 500);
        set_skill("sword", 500);
        set_skill("qixing-jian", 500);
        set_skill("tonggui-jian", 500);
        set_skill("quanzhen-jian", 500);
        set_skill("whip", 500);
        set_skill("tiangang-chenfa", 500);
        set_skill("jingluo-xue", 500);
        set_skill("taoism", 500);
        set_skill("literate", 500);
        set_skill("martial-cognize", 500);

        map_skill("force", "xiantian-gong");
        map_skill("sword", "quanzhen-jian");
        map_skill("whip", "tiangang-chenfa");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "jinguan-yusuo");
        map_skill("unarmed", "xiantian-gong");
        map_skill("finger", "yiyang-zhi");
        map_skill("strike", "haotian-zhang");
        map_skill("hand", "qixing-shou");

        prepare_skill("unarmed", "xiantian-gong");;  

        create_family("全真教", 1, "掌教");        
        // npc的pfm
        set("pfm", ({
             "unarmed.dang", 
             "unarmed.fen",
             "unarmed.hun", 
             "unarmed.jian", 
             "parry.suo",         
         }));
        //npc的兵器
        set("hand","/d/city/npc/obj/tieshou"); 


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




