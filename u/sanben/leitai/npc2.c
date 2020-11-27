
//��̨npc2

#include <ansi.h> 
inherit  __DIR__"leitai_npc";
void do_disappear();
void create()
{           
        set("level", 2);        
        set("name", "ŷ����");
        set("id", "ouyang feng");     
     
        set("long", "�����ǰ���ɽׯ�����ųơ���������ŷ���档����������\n"
                    "�����⺷����Ȼ�ܵ�������ƭ��ѧϰ�ˡ������澭������\n"
                    "����ħ��һ�ȱ�þ�����ң�����������Ȼ�ָ���������\n"
                    "ʤ������\n");
        set("title", "�������ɽׯ��");
        set("gender", "����");
        set("age", 53);
        set("nickname", HIR "����" NOR);
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

        create_family("ŷ������", 5, "����");
   
        // npc��pfm
        set("pfm", ({
             "staff.chan", 
             "staff.qianshe",
             "staff.wuji", 
             "cuff.rou",              
         }));
        //npc�ı���
        set("weapon","/d/baituo/obj/tiezheng"); 

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




