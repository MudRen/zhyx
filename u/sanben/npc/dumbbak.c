//��Ʊ�Ǽ�Ա

#include <ansi.h>

#define  SAVE_FILE      "/data/lot/sign.o" 

inherit NPC;

//int accept_ask(object ob,object me,string arg);
//mixed do_list();

void create()

{
    set_name(HIC"Ϲ��"NOR, ({"xia daben", "daben", "dumb" }));
    set("title", HIW"��"HIG"Ԫ�����﷢��Ա"HIW"��"NOR);
    set("gender", "����");
    setup();
}

void init()
{
     object me;
     ::init();

        add_action("do_list", "list");
        add_action("do_delete", "delete");
        add_action("do_delete2", "delete2");
        add_action("do_add", "add");
        add_action("do_add2","add2");


        if( interactive(me = this_player()) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, me);
        }

}

void greeting(object ob)

{
     object me;
     me=this_player();
     if (!ob || !present(ob, environment())) return;

            write(HIG"Ϲ��˵��������Ҫ��Ʊ������ask dumb about "NOR 
                                 HIY "��Ʊ\n"
                     "            list" NOR HIG"���Բ�ѯ����Щ�����á�\n"NOR
                  HIW"            ��ʦ�Ѿ��Ա���id���й������ˡ�\n\n"NOR);     
     return ;
}

mixed do_list()
{
    object me;
    string msg;
    int i;

    me = this_player();

      if ( time() - me->query_temp("last_sign") < 5 )
    
        return command("say ��ող��鷳���ң��Ȼ���˵�ɣ�\n");

    me->set_temp("last_sign", time());    
    restore_object(SAVE_FILE,1);

    msg = HIY"Ŀǰ����" + sizeof(query("mark")) + "���������Ž�Ʊ��\n"NOR HIG;
    
    if ( sizeof(query("mark")) > 0 )
    {
       for(i=0;i<sizeof(query("mark"));i++)
       {
          msg += query("mark")[i];
          if ( i < sizeof(query("mark")) - 1 ) msg += "��";
          if ( (i+1) % 5 == 0 ) msg += "\n";
       }
    }

    msg += NOR HIY"\nĿǰ����" + sizeof(query("mark2")) + "������һ�Ž�Ʊ��\n"NOR HIG;
    if ( sizeof(query("mark2")) > 0 )
    {
       for(i=0;i<sizeof(query("mark2"));i++)
       {
          msg += query("mark2")[i];
          if ( i < sizeof(query("mark2")) - 1 ) msg += "��";
          if ( (i+1) % 5 == 0 ) msg += "\n";
       }
    }
    tell_object(me, msg + NOR"\n");    
    return 1;
}

int accept_ask(object me,string arg)
{     
     string *mark, *mark2;
     object ob, piao1, piao2;
     int i;

  //   if (arg != "�����齱" && arg != "����" && arg != "�齱����")

    if (arg != "��Ʊ" && arg != "����")

     return 0;
    
     ob = this_object();
    
     mark = ({});

     
     if ( time() - me->query_temp("last_sign") < 5 )
     {
        command("say ��ող��鷳���ң��Ȼ���˵�ɣ�\n");
        return 1;
     }
 
     me->set_temp("last_sign", time());  

     restore_object(SAVE_FILE);  

     if ( sizeof(query("mark")) > 0 )       
          mark = query("mark");

     for(i=0; i<sizeof(mark); i++) 
     {

        if ( mark[i] == me->query("id"))
        {  
            command("say ���ܵõ����Ž�Ʊ��ף��齱���ˣ�");
            piao1 = new("/u/sanben/yuanxiao/lot_card");
            piao2 = new("/u/sanben/yuanxiao/lot_card");
            piao1->move(me);
            piao2->move(me);
	     message_vision(HIW"Ϲ���ó����Ų�Ʊ��$N��\n"NOR, me);
            mark -= ({ me->query("id")});
            ob->set("mark", mark); 
            assure_file(SAVE_FILE);
            save_object(SAVE_FILE,1);
            return 1;
        }
     } 

     if ( sizeof(query("mark2")) > 0 )       
          mark2 = query("mark2");

     for(i=0; i<sizeof(mark2); i++) 
     {

        if ( mark2[i] == me->query("id"))
        {  
            command("say ���ܵõ�һ�Ž�Ʊ��ף��齱���ˣ�");
            piao1 = new("/u/sanben/yuanxiao/lot_card");
           
            piao1->move(me);
            
	     message_vision(HIW"Ϲ���ó�һ�Ų�Ʊ��$N��\n"NOR, me);
            mark2 -= ({ me->query("id")});
            ob->set("mark2", mark2); 
            assure_file(SAVE_FILE);
            save_object(SAVE_FILE,1);
            return 1;
        }
     }    

    
    command("say �Բ��𣬼�¼������û��������֡�");

     return 1;
}

int do_delete( string arg )
{
    object me;
    int i, same;
    string *mark;

    me = this_player();    
    same = 0;    
    mark = ({});

    if ( ! wizardp(me) ) return 0;
    if ( ! arg ) return notify_fail(HIR"��Ҫ���ĸ�idɾ����A�����?\n"NOR);

    restore_object(SAVE_FILE, 1);  

    if ( ! query("mark") ) return notify_fail(HIR"Ŀǰû��A����ҡ�\n"NOR);
    
    for(i=0;i<sizeof(query("mark"));i++)
    {
       if ( query("mark")[i] == arg ) 
       {
           same = 1;    
           break;  
       }        
    }
    if ( same == 0 ) return notify_fail(HIR"A�������û��" + arg + "���id��\n"NOR);
    
    mark = query("mark");
    mark -= ({ arg });

    set("mark", mark);

    write(HIG"�ɹ���" + arg + "���idɾ����A����ҡ�\n"NOR);
    save_object(SAVE_FILE,1);
    return 1;
}

int do_delete2( string arg )
{
    object me;
    int i, same;
    string *mark;

    me = this_player();    
    same = 0;
    set("mark2", ({}) );

    if ( ! wizardp(me) ) return 0;
    if ( ! arg ) return notify_fail(HIR"��Ҫ���ĸ�idɾ����B�����?\n"NOR);

    restore_object(SAVE_FILE,1);  

    if ( ! query("mark2") ) return notify_fail(HIR"Ŀǰû��B����ҡ�\n"NOR);
    
    for(i=0;i<sizeof(query("mark2"));i++)
    {
       if ( query("mark2")[i] == arg ) 
       {
           same = 1;    
           break;  
       }        
    }
    if ( same == 0 ) return notify_fail(HIR"B�������û��" + arg + "���id������\n"NOR);
    
    mark = query("mark2");
    mark -= ({ arg });

    set("mark2", mark);

    write(HIG"�ɹ���" + arg + "���idɾ����B����ҡ�\n"NOR);
    save_object(SAVE_FILE,1);
    return 1;
}


int do_add( string arg )
{
    object me;
    int i, same;
    string *mark;

    me = this_player();    
    same = 0;
    mark = ({});

    if ( ! wizardp(me) ) return 0;
    if ( ! arg ) return notify_fail(HIR"��Ҫ��A������������ĸ�id?\n"NOR);

    restore_object(SAVE_FILE,1);      
    
    for(i=0;i<sizeof(query("mark"));i++)
    {
       if ( query("mark")[i] == arg ) 
       {
          same = 1; 
          break;
       }      
    }
    if ( same == 1 ) return notify_fail(HIR + arg + "���id�Ѿ���A��������ˣ�\n"NOR);
    

     if ( sizeof(query("mark")) > 0 )       
          mark = query("mark");
   
    mark += ({ arg });

    set("mark", mark);

    write(HIG"�ɹ���" + arg + "���id���ӽ�A����ҡ�\n"NOR);
    save_object(SAVE_FILE,1);
    return 1;
}

int do_add2( string arg )
{
    object me;
    int i, same;
    string *mark;

    me = this_player();    
    same = 0;
    mark = ({});

    if ( ! wizardp(me) ) return 0;
    if ( ! arg ) return notify_fail(HIR"��Ҫ��B������������ĸ�id?\n"NOR);

    restore_object(SAVE_FILE,1);      
    
    for(i=0;i<sizeof(query("mark2"));i++)
    {
       if ( query("mark2")[i] == arg ) 
       {
          same = 1; 
          break;
       }      
    }
    if ( same == 1 ) return notify_fail(HIR + arg + "���id�Ѿ���B��������ˣ�\n"NOR);   

    if ( sizeof(query("mark2")) > 0 )       
          mark = query("mark2");

    mark += ({ arg });

    set("mark2", mark);

    write(HIG"�ɹ���" + arg + "���id���ӽ�B����ҡ�\n"NOR);
    save_object(SAVE_FILE,1);
    return 1;
}

