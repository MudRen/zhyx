
//Ȥζ�������ļ�   ���ߣ�Ϲ����  (����ԭ��ʦ������ı�)
//��ƽ��һ��д�������������˵㣬����

                      
#include <ansi.h>

#define TAKE_NPC    "/u/sanben/xquest/npc/take_npc.c"//��������NPC��ԭ���ļ�
#define SET_QUEST   "/u/sanben/xquest/set_quest.c" //�������������Ϣ���ļ�
#define TOTAL_QUEST  8  //�Ӽ��������������ȡ
#define LETTER      "/clone/misc/letter.c"         //������ŵ�·��
#define RECEIPT     "/clone/misc/receipt.c"        //�����ִ��·��
#define BAG         "/u/sanben/xquest/obj/bag.c"   //�񱦻�ͼ������NPC���İ���
#define SET_ITEM    "/u/sanben/xquest/set_item.c"  //��������item���ļ�
#define HULU_INSIDE  "/u/sanben/obj/hulu_inside"   //�Ͻ��«�ڲ���·��


//�������������ȡ����
int accept_ask(object npc,object me,string topic)
{      
        
         
        int div, add;
         

         if ( me->is_busy() )
          {
                write("����æ�أ�û�ո��˴�����Ϣ��\n");
                return 1;
         }

         if ( time() - me->query("xquest/last_ask") < 5 )
         {
                write("�������������˼Ҳ�����?\n");
                return 1;
         }
         if ( time() - me->query("xquest_total_ask/time") > 3600 * 24 )
         {
                me->delete("xquest_total_ask");
                me->set("xquest_total_ask/time", time());
         }
         else
         {
         if ( me->query("xquest_total_ask/total") >= 3000
              && me->query("combat_exp") < 2000000)
         {
            message_vision(CYN "$N" CYN "����$n���˿���˵�������Բ���24Сʱ��"
                            "ֻ����3000�����񣡡�\n"NOR,
                            npc, me);
                        return 1;
         }
      }
        
          if ( me->query("xquest/mirror") )
         {
            message_vision(CYN "$N" CYN "˵���������������һ����������"
                            "���ٸ�������������\n"NOR,
                            npc, me);
                        return 1;
         }
        me->set("xquest/last_ask", time() );

        //���������񣬲�����(�жϻش��Ƿ���ȷ��Ч)
        if ( me->query("xquest/init_npc") == npc->name() &&
             me->query("xquest/kind") == "guess_riddle" )

        {
           if ( time() - me->query("xquest/time") > 300 )

           {
              message_vision(WHT "$N" WHT "��$n˵�������ܱ�Ǹ�����Ѿ�����"
                             "�ش������ʱ���ˣ���\n"NOR, npc, me);
              return 1;
           }
           tell_object(me, WHT "���" + npc->name() + "˵������"
                       "�յ��ǲ���"NOR HIG + topic + NOR WHT"�أ���\n");

           message("vision",WHT + me->name() + "��" + npc->name() + "˵��"
                    "�����յ��ǲ���"NOR HIG + topic + NOR WHT"�أ���\n"NOR,
                    environment(me),({me}));


           if ( topic != me->query("xquest/answer") )
           {
              message_vision(WHT "$N" WHT "��$n˵�������ܱ�Ǹ���´���Ӵ��"
                             "�Ǻǣ���\n"NOR, npc, me);

              tell_object(me, HIR "�㻹��" + chinese_number(300 - time() +
                              me->query("xquest/time") ) +
                              "����ʱ������\n"NOR);

              return 1;
           }
           if ( topic == me->query("xquest/answer") )
           {
              message_vision(HIC "$N" HIC "��$n˵�������ۣ��¶��ˣ��������"
                             "����\n"NOR, npc, me);

              div = 4;     //���ò���������������Ĳ���
              add = 80;
              call_other(XQUEST,"reward",me, div, add);

              return 1;
           }
        }

        if ( topic != "����" )
        return 0;

        if ( me->query("xquest/init_npc") == npc->name() )
        {
           message_vision(HIY "$N" HIY "���ͷ��ض�$n" HIY "˵��������������ô"
                                 "��ô���£��Ҳ����Ѿ�������Ҫ���ɶ���𣡡�\n"
                                 NOR, npc, me);
           return 1;
        }

        if ( me->query("xquest/target_npc") != npc->name() )
        {  return 0; }

        if ( me->query("xquest/kind") != 0 )
        {
           message_vision(HIY "$N" HIY "��$n" HIY "˵��������......����"
                                 "Ҫ��û����ɾ�ȥ�����������ȡ���ɣ���\n"NOR,
                                 npc, me);
           return 1;  
        }


       switch(random(TOTAL_QUEST))
        {    
        case 0 :
                me->start_busy(2);                
                call_other(XQUEST, "send_letter", me, npc);
                break;
        case 1 :
                me->start_busy(2);               
                call_other(XQUEST, "buy_thing", me, npc);
                break;
        case 2 :
                me->start_busy(2);                
                call_other(XQUEST, "buy_thing", me, npc);
                break;

        case 3 :
                me->start_busy(2);               
                call_other(XQUEST, "take_npc", me, npc);
                break;

        case 4 :                
                call_other(XQUEST, "pay_gold", me, npc);
                break;
        case 5 :                
                call_other(XQUEST,"do_drawing", me, npc);
                break;
        case 6 :               
                call_other(XQUEST, "take_npc", me, npc);
                break;
        case 7 :                
                call_other(XQUEST, "guess_riddle", me, npc);
                break;
         default:
                 me->start_busy(2);               
                call_other(XQUEST, "buy_thing", me, npc);
                break;

        } 
        return 1;
}

//��һ���������Ÿ�ָ��NPC(�Ȳ����ż���Ŀ��NPC��
void send_letter(object me, object init)
{
       object ob, letter;
       string npc, place, name;

       
       npc = call_other(SET_QUEST, "set_npc");
       sscanf(npc, "%s/%s", place, name);

       if ( name == 0 || name == "" || name == init->name())
       //���Ŀ��NPC���������NPCΪͬһ��
          {

            call_other(XQUEST,"send_letter", me, init);
            return;
          } //�����º��к����ٴγ�ȡ����

      if ( name != 0 && name != ""  &&  name != init->name() )
        //ȡ����Ч�������Ժ�
       {
           me->set("xquest/kind", "send_letter");  //��¼��������Ϊ����
           me->set("xquest/init_npc", init->name()); //��¼���������NPC������
           me->set("xquest/target_npc", name);  //��¼Ŀ��NPC������
           me->set("xquest/place", place);      //��¼Ŀ��NPC���ڵĵص�
           me->set("xquest/time", time());     //��¼����ʼ��ʱ��
           letter = new(LETTER);
           letter->set("long", "����һ��" + init->name() + "д��" +
                             name + "���ױ��ź���\n");
           letter->set("init_npc", init->name());
           letter->set("target_npc", name);
           letter->move(me);

           tell_object(me, WHT + init->name() + "�����������˵������" +
                       "������鷳�㾡������͵�"NOR HIY + place + WHT"��"HIY +
                       name + NOR WHT"���\n"
                       "Ȼ���ٰѻ�ִ�û������Ҿ͸��������Ϣ����\n"NOR  +
                       init->name() + "˵�ž��ó�һ���Ÿ��㡣\n");

            message("vision",WHT + init->name() + "��" + me->name() +
                    "����С���Ը���ʲô��\n" + me->name() + "һ������"
                    "һ�߲�ס�ص�ͷ ��\n"NOR +  init->name() +
                    "˵����ó�һ���Ž�����" +  me->name() + "��\n",
                    environment(init),({me}));
      }
      return;
}


//���������񣬰�NPC���� (��������������)

void buy_thing(object me, object init)
{
       object item;
       string item_path, item_name,msg;

       item_path = call_other(SET_QUEST, "set_item");
       item = new(item_path);


       if ( item == 0 )
       {
           call_other(XQUEST,"buy_thing", me, init);
           return;
       }
       else  {

             item->move(init);
             item_name = ( find_object(item_path)->name() );
             destruct (item);
          if ( sizeof(filter_color(item_name)) > 0 )
          {
            tell_object( me,WHT + init->name() + "�����������˵������"
                       "�������Ҳ���"NOR + item_name + WHT
                       "��Ҫ���ܰ��Ұ��ⶫ�������Ҿ͸��������Ϣ����\n");
          }
          else
          {
            msg = call_other(TEXT2PIC_D,"Display",filter_color(item_name));
            tell_object( me,WHT + init->name() + "�����������˵������"
                       "�������Ҳ���һ������,"
                       "��Ҫ���ܰ��Ұ��ⶫ�������Ҿ͸��������Ϣ����\n"NOR);
            write(msg +"\n");
          }

          message("vision",WHT + init->name()
                  + "��" + me->name() +  "����С���Ը���ʲô��\n" +
                  me->name() + "һ������һ�߲�ס�ص�ͷ ��\n"NOR,
                  environment(me),({me}));

           me->set("xquest/kind", "buy_thing");  //������������Ϊ����
           me->set("xquest/init_npc", init->name()); //���÷��������NPC������
           me->set("xquest/target_npc", init->name());  //����Ŀ��NPC������
           me->set("xquest/item", item_name );
           me->set("xquest/time", time());     //��������ʼ��ʱ��
                                             //��������ַ��������
                }
           return;

}

//���������񣬻���NPCȥĳ���ط� (��������������)
void take_npc(object me, object npc)
{
       object ob;
       string place, place1, place2;

       place = call_other(SET_QUEST, "set_place");
         if ( place == 0 || place == "")
       {
           call_other(XQUEST, "take_npc", me, npc);
           return;
       }

      if ( place != 0 && place != "")   {

        sscanf(place, "%s/%s", place1, place2);
      

        ob = new(TAKE_NPC);
        ob->move(environment(npc));
        ob->set("long", "����" + npc->name() +
                        "��Զ�����ݡ�\n");
        ob->set("leader",me);
        ob->set_leader(me);
        ob->set("dest", place2);

        me->set("xquest/kind", "take_npc");
        me->set("xquest/init_npc", npc->name());
        me->set("xquest/target_npc", ob->name());
        me->set("xquest/place1", place1);
        me->set("xquest/place2", place2);
        tell_object(me, WHT + npc->name() + "�����������˵������"HIY +
                   ob->name() + NOR WHT"����һλԶ�����ݡ�\n"
                   "��������˥���н���ľ����������ǰ��ȥ��"HIG + place1 +
                   NOR WHT"��"HIG + place2 + NOR
                   WHT"��ȴ���һ׮��Ը��\n������������һ�̡�"
                   "�ȵ��˵�ͷ����Ȼ�����������֪�������顣��\n"NOR);

        message("vision",WHT + npc->name() + "��" + me->name() +
                 "����С���Ը���ʲô��\n" + me->name() + "һ������"
                 "һ�߲�ס�ص�ͷ ��\n"NOR,
                environment(ob),({me}));

        
         call_other(XQUEST,"create_npc",ob);
         return;
              }
}

//����NPCȥĳ�������ӳ�1�����NPC���ֵ�����
void create_npc(object ob)
{

     message_vision(CYN "ֻ��$N" CYN "�������ǵ��߹���,��" "$n" CYN
                    "���˸�Ҿ�������Ϻ���ʱ���޶��ˣ�����������̰ɡ���\n"NOR,
                    ob, this_player());
     //����������,�ⲿ��ȡ��
     if ( this_player()->query("combat_exp") >500000 && random(30) == -1 )
     {
        message_vision(HIY "$N" HIY "��Ҫ�ٲ���ͻȻֻ����Ǵ�������һ������"
                       "Ʈ�˹����������ܻ���˵����\n����������������������"
                       "�������˵�α��֮ͽ�����쿴�����������" NOR + HIR"C"NOR
                       HIM"O"NOR HIY"L"NOR HIG"O"NOR HIB"R"NOR HIR" SEE SEE��"
                       HIY"��\n"NOR, this_player());
        message_vision(HIW"ֻ����Ǵ����������е��Ͻ��«�����һ������������"
                       "$N��ʱ����һ�����̱��ս��˺�«�����\n\n"NOR,
                       this_player());
        this_player()->move(HULU_INSIDE);
     }
}

//���������񣬸�NPC�ƽ�����(�˴���������)
void pay_gold(object me, object npc)
{
     
     int amount;

     me->set("xquest/kind","pay_gold");
     me->set("/xquest/init_npc",npc->name());

     amount = random(50) + 1;
     
     me->set("xquest/pay_amount", amount);

     tell_object(me, WHT + npc->name() + "¶��һ˿���ε����飬�����������˵"
                     "��������...�����...�������ͷ�е����\n��Ҫ���ܸ���"NOR
                     HIY + chinese_number(amount) + "��"NOR + HIW"����"NOR +
                     WHT"�Ҿ͸��������Ϣ����\n"NOR);

     message("vision",WHT + npc->name() + "¶��һ˿���ε����飬������" +
                      me->name() + "����˵�˵�ʲô��\n",
                      environment(npc),({me}));
     return;


}

//���������񣬰�NPC�񱦱�����ͼ
void do_drawing(object me, object npc)
{
       object ob;
       string place, place1, place2;

       
       place = call_other(SET_QUEST, "set_place");
                
         if ( place == 0 || place == "")
       {
           call_other(XQUEST,"do_drawing",me, npc);
           return;
       }
        if ( place != 0 && place != "")

       {
           sscanf(place, "%s/%s", place1, place2);
           me->set("xquest/kind", "do_drawing");  //������������Ϊ��ͼ
           me->set("xquest/init_npc", me->query("xquest/target_npc"));
            //���÷��������NPC������

           me->set("xquest/place1", place1);
           me->set("xquest/place2", place2);  //��¼�񱦵ĵص�
           me->set("xquest/buried", 0);    //��¼������δ���
           tell_object( me,WHT + me->query("xquest/init_npc") +
                "�����������˵���������������һ�ʺ�ƣ�������������\n"
                "����Ұ�����"NOR HIY + place1 + NOR WHT "��" NOR HIY +
                place2 + NOR WHT"ȥ���ٰ������"
                "���λ����������ң��������պ����ȥȡ��\n"
                "һ�ж����׺������г�л����\n");

                message("vision", WHT + me->query("xquest/init_npc") +
                "��" + me->name() +  "����С���Ը���ʲô��\n" +
                me->name() + "һ������һ�߲�ס�ص�ͷ ��\n"NOR,
                environment(me),({me}));
           ob = new(BAG);
           ob->move(me,1);
           message_vision(CYN "$N" CYN "�ó�һ��������$n��\n",
                               npc, me);
               return;
            //�����񱦻�ͼ���񷢷����
       }
}

//���������񣬲����� (�������

void guess_riddle(object me, object init)
{
       object ob;
       string riddle, pro, ans, *space;
       int i;

       space = ({"!","@","#","$","%","^","&","*","_","+","|"});

       riddle = call_other(SET_QUEST, "set_riddle");
       sscanf(riddle, "%s:%s", pro, ans);

       if ( pro == 0 || pro == "" )
       //���ȡ��������Ϊ��
          {
            call_other(XQUEST,"guess_riddle", me, init);
            return;
          } //�����º��к����ٴγ�ȡ����
        if ( pro != 0 && pro != "" )
        {

       /*    i = random(10);
           if ( i%2 == 0 ) i = i -1;
           pro = pro[0..i] + space[random(sizeof(space))] +
                 space[random(sizeof(space))] + pro[(i+1)..sizeof(pro)];

           i = random(10);
           if ( i%2 == 0 ) i = i -1;
           pro = pro[0..i] + space[random(sizeof(space))] +
                 space[random(sizeof(space))] + pro[(i+1)..sizeof(pro)];

           i = random(10);
           if ( i%2 == 0 ) i = i -1;
           pro = pro[0..i] + space[random(sizeof(space))] +
                 space[random(sizeof(space))] + pro[(i+1)..sizeof(pro)]; */

        message_vision(WHT "$N" WHT "��$n˵�������ҽ�������ģ������������"
                      "���������Ϸ�ɣ�Ҫ�ǲ¶����Ҿ͸��������Ϣ����\n"NOR,
                      init, me);
         tell_object(me, HIG + pro +
                  NOR HIY"\nָ���� ask npc<id> about �յ�    " NOR +
                  HIR"�����������ڻش�\n"NOR);
        me->set("xquest/kind", "guess_riddle");
        me->set("xquest/init_npc", init->name() );
        me->set("xquest/riddle", pro);
        me->set("xquest/answer", ans);
        me->set("xquest/time", time());
        return;
        }
}



//�������ʱ�ķ�Ӧ
int accept_object(object me, object ob, object npc)
{
    int div, add,amount;    //���ݲ�ͬ������㽱���Ĳ���
    object receipt, pay;
    string change_npc;

     if ( me->is_busy() )
          {
                write("����æ�أ�û�ս����������ˣ�\n");
                return 0;
         }

    if ( time() - me->query("xquest/last_give") < 5 )
         {
                write("���������Ÿ������˼Ҳ�����?\n");
                return 0;
         }
        
        me->set("xquest/last_give", time() );
       

      
  //  if ( npc == 0 ) { npc = this_object();}


    if ( me->query("xquest/target_npc") != npc->name())//������Ŀ��NPC
       return 0;                                       //�򲻽����κ����

    if ( me->query("xquest/kind") == "send_letter")    //�������������
    {
       if ( ob->query("target_npc") != npc->name() )  /*������ż����Ǹ�Ŀ��
                                                       NPC�� */
       {
           tell_object( me, npc->name() + "���˿��ţ�����˵����"
                        "���������Ǹ��ҵ���ѽ����\n");
                        return 0;
       }
       else
       {
            if ((time() - me->query("xquest/time")) > 600 )//�������ʱ����͵�
            {

                message_vision(CYN "$N" CYN "�����ض�$n˵����������ô"
                               "��ô�ٲŰ����������ѽ���������ҵĴ����ˣ���\n",
                               npc, me);
                tell_object(me, HIR"�㿴��" + npc->name() + "�����Ĺĵ�����" +
                            "���������ǿ϶������ٸ�������һ���������ˡ�\n"NOR);
                return 1;
            }                  //����ʧ�ܣ����ṩ��һ������


            message("vision",WHT + npc->name() + "�ӹ��ſ��˿��������" +
                     "˵��������л��λ" + RANK_D->query_respect(me)
                     + "�����͵�����\n"NOR,
                    environment(me));     //�����ż�������
            destruct(ob);                 //���ٵ��յ����ż��������
            //�˴���ʼ�ڶ��������͵��ź󽫻�ִ����ԭNPC

            me->set("xquest/kind", "bring_receipt");  //������������Ϊ�ͻ�ִ

            change_npc = me->query("xquest/init_npc");//��ԭ��������ߴ浽��

            me->set("xquest/init_npc", me->query("xquest/target_npc"));
            //�����������ͻ�ִ��������Ϊԭ�������ţ���Ŀ��NPC

            me->set("xquest/target_npc", change_npc);
             //��change_npc����ȡ��ԭ���񷢳��ߣ���Ϊ������Ŀ��NPC

            me->set("xquest/time", time());     //��������ʼ��ʱ��
            receipt = new(RECEIPT);
            receipt->set("long", "����һ��" + me->query("xquest/init_npc") +
                                 "����" + change_npc + "�Ļ�ִ��\n");
            receipt->set("init_npc", me->query("xquest/init_npc"));
            receipt->set("target_npc", change_npc);
                                          //���Ͻ����������Ϣ��¼����ִ��
            receipt->move(me);

            message_vision(CYN "$N" CYN "�ó�һ���ִ��" "$n��\n"NOR,
                    npc, me);                    //������ִ������

              return 1;
        }
    }

    /*��ʼ�ڶ���������ܻ�ִ���ж�
     �Ƿ��ǽ���Ŀ��NPC��������ʼ���жϣ��˴��Թ� */

     if ( me->query("xquest/kind") == "bring_receipt")    //������ͻ�ִ������
    {
       if ( ob->query("target_npc") != npc->name() )  /*����˻�ִ���Ǹ�Ŀ��
                                                       NPC�� */
       {
           tell_object( me, npc->name() + "���˿���ִ������˵����"
                        "������ִ�����Ǹ��ҵ�ѽ����\n");
                        return 0;
       }
       else
       {
           if ((time() - me->query("xquest/time")) > 300 )//�������ʱ����͵�
            {

                message_vision(CYN "$N" CYN "�����ض�$n˵����������ô"
                               "��ô�ٲŰѻ�ִ����ѽ�����ҵ�������ô���죡��\n"
                               "˵���ת��ͷȥ��Ҳ�����$n�ˡ�\n" NOR,
                               npc, me);
                tell_object(me, HIR"����������һ�������������ˡ�\n"NOR);
                return 1;
            }                  //����ʧ�ܣ����ṩ��һ������

            message("vision",WHT + npc->name() + "�ӹ���ִ���˿��������" +
                     "˵��������л��λ" + RANK_D->query_respect(me)
                     + "���������æ����\n"NOR,
                    environment(me));     //���ܻ�ִ������
             destruct(ob);               //���ٵ���ִ���������
             div = 4;     //�����ͻ�ִ����������Ĳ���
             add = 80;

             message_vision(CYN "$N�ӻ����ͳ�һЩ���ӽ���$n��˵����������Ǹ�"
                               "������ȷѡ���\n" NOR,
                               npc, me);

             pay = new("/clone/money/silver");
             pay->set_amount(5+random(5));
             pay->move(me, 1);

             call_other(XQUEST,"reward",me, div, add);  //���н�������
             return 1;                            //�ͻ�ִ���񵽴����
       }
     }

     if ( me->query("xquest/kind") == "buy_thing")    //�������������
    {
        if ( ob->name() != me->query("xquest/item") ) //�������NPCҪ�Ķ���

        { message_vision(CYN "$N" CYN "��$n�ɻ��˵�������ף����"
                               "��������Ҫ�Ķ���ѽ����\n" NOR,
                               npc, me);
          return 0; }

        if ((time() - me->query("xquest/time")) > 600 )//�������ʱ����͵�
        {
          message_vision(CYN "$N" CYN "��мһ�˵ض�$n˵����������ô�ٲŰ�"
                               "�ⶫ������������ǰ�����Ѿ��ҵ��ˣ���\n" NOR,
                               npc, me);
          tell_object(me, HIR"���ˣ�����û��������������ˣ���ͷ�����ɡ�\n"NOR);
          return 0;
        }    //�Ҷ�������ʧ�ܣ����ṩ��һ������

        else
        {
            message("vision",WHT + npc->name() + "�ӹ�"NOR + ob->name()+NOR WHT
                    "���˿��������˵��������л��λ" + RANK_D->query_respect(me)
                     + "�����������æ����\n"NOR,
                    environment(me));     //���ܹ�����Ʒ������
            
            message_vision(CYN "$N�ӻ����ͳ�һ�����ӽ���$n��˵����������Ǹ�"
                               "������ȷѡ���\n" NOR,
                               npc, me);

             pay = new("/clone/money/silver");
             amount = ob->query("value") /100 + 1 + random(6);
             if ( amount < 6 ) amount = 6;
             pay->set_amount(amount);

             pay->move(me,1);             //������ԭ��Ʒ�ļ�ֵ + n silver

              destruct(ob);                 //���ٵ��յ�����Ʒ�������
             div = 4;     //�����Ҷ�������������Ĳ���
             add = 100;

             call_other(XQUEST,"reward",me, div, add);  //���н�������
             return 1;                            //�Ҷ������񵽴����

        }
    }

     if ( me->query("xquest/kind") == "pay_gold")    //����Ǹ�Ǯ����������
    {
       if ( ! ob->query("money_id") )  //������Ĳ���Ǯ
       {
              message_vision(CYN "$N��$n������˵��������Ҫ���͸�Ǯ��Ҫ��"
                                 "����·��������Щ�����������ң���\n" NOR,
                               npc, me);
              return 0;
       }
       if ( ob->value() / 100 < me->query("xquest/pay_amount") ) //����Ǯ����
       {
              message_vision(CYN "$N��$n������˵��������������ô��ô��������"
                                 "�ģ�\n�ϸ���ˬ������"NOR  +
                                 chinese_number(me->query("xquest/pay_amount"))
                                 + "��" + HIW"����" NOR CYN +
                                 "��Ҫ�᲻�þͳ������������������£���\n" NOR,
                                 npc, me);
              return 0;
       }
       else
       {     if ( random(3) == 1 )
             { message_vision(CYN "$N�ӹ�$n�������Ļƽ𣬶�ʱϲ��ü�ң�"
                                 "����˵��������,��,�����������£��ٺ٣���\n"
                                 "��һ���������࣬�������������¡�\n"NOR ,
                                 npc, me);
               destruct(ob);         //���ٵ��յ���gold�������

           call_other(XQUEST,"next_quest",me);  //����next_quest���������µ�����

              return 1;
              }
              else
              {

               tell_object( me,WHT + npc->name() +
                "������߹������ص�˵��������λ" + RANK_D->query_respect(me) +
                "�Һ���˵ʵ���ɣ��ղ���ֻ�����������Ʒ��Ρ�\n"
                "����ּ�Ȼ��˴󷽣�����������ҿ�������ȥ���ˣ���\n"NOR);

                //�˴����в�������������ĺ�������NPC�񱦱��ٻ�ͼ

               call_other(XQUEST,"do_drawing", me, npc);

                return 0;
               }
       }
    }
       //�˴��ж��Ƿ����ͼ��
      if ( me->query("xquest/kind") == "do_drawing")    //������񱦻�ͼ����
    {
        if ( me->query("xquest/init_npc") != npc->name() )//���������NPC���ŵ�
        return 0;

        if ( ! ob->id("paper of drawing") )            //���Ĳ���ֽ�ŵĻ�
        return 0;

        if ( me->query("xquest/buried") == 0 )          //���û����

        {
           message("vision",WHT + npc->name() + "����һ����˵������" +
                   me->name() + "����Ϊ���ǰ׳���\n�⼸����һֱ���˸����㣬"
                   "���������ûȥ���ҵı�����\n��ʵ�������ǲ��ǰ��ҵı���̰����"
                   "Ȼ���������ͼ���������ң�����\n"NOR, environment(me));
           return 0;

        }

         if ( ! ob->query("draw/info") )
        {
           message("vision",WHT + npc->name() + "˵������" + me->name() +
                   "�����Ű�ֽ���Ҹ�ʲô���в���!��\n"NOR, environment(me));
           return 0;

        }

     if ( ob->query("draw/info") == "unknow" )
        {
           message("vision",WHT + npc->name() + "˵������" + me->name() +
                   "���⻭����ʲôӴ����\n"NOR, environment(me));
           return 0;

        }
        if ((ob->query("draw/info") )->short() != me->query("xquest/place2") )
        {
           message("vision",WHT + npc->name() + "˵������" + me->name() +
                   "��ɿ�����ˣ���Ҫ����ҵı�������"NOR HIY +
                   me->query("xquest/place2") + NOR WHT"\n�ٰ�����ĵ��λ���"
                   "�����������Ǹ��һ�������ѽ����\n"NOR, environment(me));
           return 0;

        }
        destruct(ob);
        message_vision(CYN "$N�ӹ�$n��������ͼ�����˿��������˵�������ţ���"
                           "����������ط�����һ���������ˡ�\n"
                           "��������Ǹ���ĳ��͡�˵�žʹӻ������������ӽ�"
                           "����$n��\n"NOR, npc, me);

        pay = new("/clone/money/silver");
        pay->set_amount(5 + random(5));
        pay->move(me, 1);                      //������

        div = 3;
        add = 80;                              //���ý���ϵ��


        call_other(XQUEST,"reward", me, div, add);  //���н�������
        return 1;                             //�񱦻�ͼ���񵽴˽���

    }
    return 0;
}

void reward(object me, int div, int add)      //���㽱��
{
     int exp, pot, tihui, score, weiwang, num, multi;

     me->set("xquest/kind",0);     //��������Ϊû������״̬
     me->add("xquest_count",1);   //�ۼ������������һ��
     if ( me->query("xquest_count") > 500 )
     { me->set("xquest_count",1); }     //�ۼƳ���500���1

     num = me->query("xquest_count");

   //  if ( me->query("xquest_count") < 20 ) { num = 20;}
     if ( me->query("xquest_count") > 250 ) { num = 250;}

     exp =  ( num / div + random(100) ) * 2 + add;
     pot =   num / div + random(100) + add ;


     tihui = random( num/div ) ;
    // tihui = 1 + random(2);
     tihui += 10;
     
     multi = 2;

     if ( me->query("combat_exp") > 300000 ) multi = 1;

     exp *= multi;
     pot *= multi;
     tihui *= multi;

  
     if ( me->query("combat_exp") > 2000000 )
     {
        exp /= 16;
        pot /= 16;
      //  tihui /= 16;
        tihui = 1;
     } else   
     if ( me->query("combat_exp") > 1000000 )
     {
        exp /= 8;
        pot /= 8;
      //  tihui /= 8;
        tihui = 1;
     } else
     if ( me->query("combat_exp") > 800000 )
     {
        exp /= 4;
        pot /= 4;
        tihui /= 4;
     }
       else
     if ( me->query("combat_exp") > 500000 )
     {
        exp /= 2;
        pot /= 2;
        tihui /= 2;
     }

     if ( me->query("combat_exp") < 1000000 )
     {
        score = random(50) + 10;
        weiwang = random(50) + 10;
     }
else
     {
        score = random(5) + 5;
        weiwang = random(5) + 5;

     }

     if ( me->query("potential") >= me->query_potential_limit() )
     {  pot = 1; }
     if ( me->query("experience") >= me->query_experience_limit() )
     {  tihui = 1; }

     me->add("combat_exp", exp );
     me->add("potential", pot );
     me->add("experience", tihui);
     me->add("score", score);
     me->add("weiwang", weiwang);

     me->start_busy(2);
     tell_object( me, HIG"\nͨ����ζ�����������"NOR HIR + chinese_number(exp) +
                  HIG"�㾭�飬"NOR HIW + chinese_number(pot) + NOR
                  HIG"��Ǳ���Լ�"HIY +
                  chinese_number(tihui) + HIG"��ʵս��ᡣ\n" +
                  "���������Լ�����Ҳ�����˲�ͬ�̶ȵ���ߡ�\n" NOR);

     if ( me->query("xquest_count") % 100 == 0 )  //����������������item����
     {

        call_other(XQUEST,"item_reward", me);

     }

     call_other(XQUEST,"next_quest",me);  //����next_quest���������µ�����
     return;
}

void next_quest(object me)   //������һ�����������ĺ���
{
       string npc, place, name;

       npc = call_other(SET_QUEST, "set_npc");
       sscanf(npc, "%s/%s", place, name);

       me->set("xquest/kind",0);
       me->add("xquest_total_ask/total", 1 );
  //     if ( random(40) == 1 ) me->set("xquest/mirror",1);

       if ( name == "" || name == 0 ||
             name == me->query("xquest/target_npc")
         ||  name == me->query("xquest/init_npc") )  //����µ�
          {                                   //Ŀ��NPC��Ŀǰ������NPCΪͬһ��
            call_other(XQUEST,"next_quest", me);
             return;
          }                                     //�����º��к����ٴγ�ȡ����

       if ( name != "" && name != 0 && 
             name != me->query("xquest/target_npc")
         && name != me->query("xquest/init_npc") )
          {
                tell_object( me,WHT + me->query("xquest/target_npc") +
                "�����������˵�������㲻��ȥ��"NOR HIY + place + NOR WHT"��"
                NOR HIY + name + NOR WHT"���������������������Щ��������\n");

                message("vision",WHT + me->query("xquest/target_npc")
                + "��" + me->name() +  "����С���Ը���ʲô��\n" +
                me->name() + "һ������һ�߲�ס�ص�ͷ ��\n"NOR,
                environment(me),({me}));
                me->set("xquest/place", place);
                me->set("xquest/init_npc", me->query("xquest/target_npc") );
                me->set("xquest/target_npc", name);
          }
          return;

}

void item_reward(object me)
{
        object item;
        string gift;

    if ( random(2) > -1 )
    {
        gift = call_other(SET_ITEM, "set_item", me);
        if ( gift == 0 || gift =="" )
        {
           call_other(XQUEST,"item_reward", me);

        }  else

        if ( gift != 0 && gift !="" )
        {

           item = new(gift);
           item->move(me);

           message_vision(HIC"������ʱֻ�����е��˴Ҵ�ææ��������$N˵��:����"
                           "ʦ��˵�����ڰ������ǽ����������˲��ٺ��£�\n�����"
                           "�����Ҹ����������������\n˵�žʹӻ��������㶫��"
                           "������$N\n"NOR, me);
           if ( item->query("base_unit") )
           {
              tell_object(me,HIG"������һ" + item->query("base_unit") + NOR +
              item->name()+ "\n");
           }   else
           {
           tell_object(me,HIG"������һ" + item->query("unit") +  NOR +
           item->name()+ "\n");
           }
        }
     }
      else
     {
           message_vision(HIC"������ʱֻ�����е��˴Ҵ�ææ��������$N˵��:����,"
                           "�����ڰ��������¸ɵò�������Ŭ��\n��ʱ��"
                           "�һ�������ʽ�������\n˵��ͼ����Ʒ����ˡ�"NOR, me);
     }
}


