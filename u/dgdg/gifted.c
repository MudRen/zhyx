inherit F_DBASE;
#include <ansi.h>


void create()
{
        seteuid(getuid());
        set("name", HIG "����ϵͳ��������" NOR);
        set("id", "card daemon");
        call_out("remind", 5);
}

int do_place()
{
   string *alldir, dir, dir_name, *allfile,file;
   int i;
   object place, gift;
   mapping dir_list = ([
                "/d/beijing/" : "������", 
                "/d/changan/" : "������",
                "/d/city/" : "���ݳ�",
                "/d/city3/" : "�ɶ���",
                "/d/dali/" : "�����",
                "/d/guanwai/" : "����",
                "/d/hangzhou/" : "���ݳ�",
                "/d/kaifeng/" : "�����",
                "/d/jingzhou/" : "���ݳ�",
                "/d/luoyang/" : "������",
                "/d/lingxiao/" : "������",
                "/d/quanzhen/" : "����ɽ",
                "/d/wudang/" : "�䵱ɽ",
                "/d/zhongzhou/" : "���ݳ�",
                "/d/shaolin/" : "�����µ���",
                "/d/wudu/" : "�嶾�̵���",
                "/d/xingxiu/" : "����",
                "/d/huashan/" : "��ɽ",
                "/d/emei/" : "��üɽ",
    ]);
   remove_call_out("remind");
   call_out("remind", 100);

   alldir = keys(dir_list);

   dir = alldir[random(sizeof(alldir))];
   if ( ! dir || dir == 0 ) dir = "/d/wudang/";
   dir_name = dir_list[dir];  
   
   message( "gift", BLINK HIY"���콵���" NOR HIG
            "�����ۼ��˼伲�࣬��" + dir_name + "������һЩ�����Һβ�Ⱥ���Ѱ֮��\n"NOR, users() );
 
   allfile = get_dir(dir);
  
   for(i = 0;i < 20;i++)
   {
      file = dir + allfile[random(sizeof(allfile))];

      if ( file[<2..<1] != ".c") continue;

      write(file + "\n");
      if ( find_object(file) )
         place = find_object(file);
      else 
          place = load_object(file);

      if (  place )
      {   
          if ( i > 2 && i <= 7 ) gift = new("/u/dgdg/obj/moon cake");
          else 
             gift = new("/u/dgdg/obj/giftpack.c");            
          gift->move(place);
          tell_room(place, HIC"ͻȻֻ��������ƶ���̽��ͷ��������һ��������\n"NOR);
      }
   }
   return 1; 


}

void remind()
{

   message( "gift", BLINK HIY"���콵���" NOR HIR
            "�����������Ӻ�ַ������ҪѰ����������׼����\n"NOR, users() );
   
   remove_call_out("do_place");
   call_out("do_place", 180);


} 
aaa




