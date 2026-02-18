#include <gtk/gtk.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <locale.h>
#include <libintl.h>
//#define OS_BITS (((int)((int *)0 + 1)) << 3)
#define OS_BITS (sizeof(long)<<3)
char str_processName[1024];
char str_noticeLabel[1024];
char str_Button_license[1024];
char str_Button_privacy[1024];
char str_checkButton[1024];
char str_installButton[1024];
char str_finishLabel[1024];
char str_doneButton[1024];
char licensePath[1024];
char *licenseData = NULL;
long licenseDataSize = 0;
char privacyPath[1024];
char *privacyData = NULL;
long privacyDataSize = 0;
char localeStringPath[1024];
char *localeStringData = NULL;


char* DeteteWhiteSpace(char* str)                // Delete space
{ 
        char strTemp[256];
        char strTemp2[256];
        unsigned int i,j; 
        memset(strTemp, 0, 256);
        strcpy(strTemp2, str);
        j = 0;
        if (str != NULL) 
        {
                for(i=0; i<strlen(str); i++)
                {
                        if (strTemp2[i] != ' ')
                        {
                                strTemp[j++] = strTemp2[i];
                        }
                }
        }
        strcpy(str, strTemp);
        return(str);
}

void initialzeLocalStrings()
{
    char *language = getenv("LANG");            // 获取系统语言
    printf("%s\n", language);
    
    char path[1024];
    getcwd(path, sizeof(path));                 // 获取程序路径
    snprintf(localeStringPath, sizeof(localeStringPath), "%s/locale/%s/strings.txt", path, language);   // 获取界面字符串的路径
    snprintf(licensePath, sizeof(licensePath), "%s/locale/%s/license.txt", path, language);             // 获取许可协议的路径
    snprintf(privacyPath, sizeof(privacyPath), "%s/locale/%s/privacy.txt", path, language);             // 获取隐私协议的路径

    FILE *fp = fopen(licensePath, "r,css=utf-8");   // 打开许可协议文件
    if (NULL == fp) 
    {
        // 为找到对应的许可协议文件时,使用英文的许可协议
        snprintf(licensePath, sizeof(licensePath), "%s/locale/%s/license.txt", path, "en_US.UTF-8");
        fp = fopen(licensePath, "r,css=utf-8");
    }
    if(fp)
    {
        fseek(fp, 0L, SEEK_END);    // 从哪里开始查找文件,SEEK_END表示文件尾
        
        long size = ftell(fp);      // 获取文件字节数
        licenseData = malloc(size); // 分配空间
        if(licenseData)             // 空间大小存在时
        {
            fseek(fp, 0L, SEEK_SET);    // 从文件开头读取文件内容
            size_t readSize = fread(licenseData, size, 1, fp);  // 将文件的数据读取到licenseData中
            licenseDataSize = size;                             // 获取文件大小
        }
        fclose(fp);
    }
     
    FILE *fp_privacy = fopen(privacyPath, "r,css=utf-8");   // 打开许可协议文件
    if (NULL == fp_privacy) 
    {
        // 为找到对应的许可协议文件时,使用英文的许可协议
        snprintf(privacyPath, sizeof(privacyPath), "%s/locale/%s/privacy.txt", path, "en_US.UTF-8");
        fp_privacy = fopen(privacyPath, "r,css=utf-8");
    }
    if(fp_privacy)
    {
        fseek(fp_privacy, 0L, SEEK_END);    // 从哪里开始查找文件,SEEK_END表示文件尾
        
        long size = ftell(fp_privacy);      // 获取文件字节数
        privacyData = malloc(size); // 分配空间
        if(privacyData)             // 空间大小存在时
        {
            fseek(fp_privacy, 0L, SEEK_SET);    // 从文件开头读取文件内容
            size_t readSize = fread(privacyData, size, 1, fp_privacy);  // 将文件的数据读取到privacyData中
            privacyDataSize = size;                             // 获取文件大小
        }
        fclose(fp_privacy);
    }

    FILE *strfp = fopen(localeStringPath, "r,css=utf-8");   //打开界面字符串文件
    if (NULL == strfp)
    {
        // 如果没找到,则打开英文的字符串界面
        snprintf(localeStringPath, sizeof(localeStringPath), "%s/locale/%s/strings.txt", path, "en_US.UTF-8");
        strfp = fopen(localeStringPath, "r,css=utf-8");
    }
    if(strfp)
    {
        char line[256];          
        char* pstr=(char*)NULL;    
        while(fgets(line, 256, fp) !=(char*)NULL)                 
        {                                          
            //DeteteWhiteSpace(line);
            // str_processName = Pantum Driver Installer
            if(pstr = strstr(line, "str_processName"))                             
            {                                                              
                pstr = strstr(line, "="); pstr+=2;                             
                memset(str_processName, 0, sizeof(str_processName));
                strncpy(str_processName, pstr, strlen(pstr)-1);
            }
            // str_noticeLabel = 请仔细阅读下列许可协议，您在安装前必须同意这些协议条款。
            if(pstr = strstr(line, "str_noticeLabel "))                             
            {                                                              
                pstr = strstr(line, "=");pstr+=2;                             
                memset(str_noticeLabel, 0, sizeof(str_noticeLabel));
                strncpy(str_noticeLabel, pstr, strlen(pstr)-1);                        
            }
            // str_Button_license = 许可协议
            if(pstr = strstr(line, "str_Button_license"))                             
            {                                                              
                pstr = strstr(line, "=");  pstr+=2;                              
                memset(str_Button_license, 0, sizeof(str_Button_license));
                strncpy(str_Button_license, pstr, strlen(pstr)-1);                          
            }
            // str_Button_privacy = 隐私协议
            if(pstr = strstr(line, "str_Button_privacy"))                             
            {                                                              
                pstr = strstr(line, "=");  pstr+=2;                              
                memset(str_Button_privacy, 0, sizeof(str_Button_privacy));
                strncpy(str_Button_privacy, pstr, strlen(pstr)-1);                          
            }
            // str_checkButton = 我同意
            if(pstr = strstr(line, "str_checkButton"))                             
            {                                                              
                pstr = strstr(line, "=");  pstr+=2;                              
                memset(str_checkButton, 0, sizeof(str_checkButton));
                strncpy(str_checkButton, pstr, strlen(pstr)-1);                          
            }
            // str_installButton = 安装
            if(pstr = strstr(line, "str_installButton"))                             
            {                                                              
                pstr = strstr(line, "=");  pstr+=2;                              
                memset(str_installButton, 0, sizeof(str_installButton));
                strncpy(str_installButton, pstr, strlen(pstr)-1);                           
            }
            // str_finishLabel = 安装完成
            if(pstr = strstr(line, "str_finishLabel"))                             
            {                                                              
                pstr = strstr(line, "=");  pstr+=2;                              
                memset(str_finishLabel, 0, sizeof(str_finishLabel));
                strncpy(str_finishLabel, pstr, strlen(pstr)-1);                           
            }
            // str_doneButton = 完成
            if(pstr = strstr(line, "str_doneButton"))                             
            {                                                              
                pstr = strstr(line, "=");   pstr+=2;                             
                memset(str_doneButton, 0, sizeof(str_doneButton));
                strncpy(str_doneButton, pstr, strlen(pstr)-1);                           
            }
        } 
        fclose(strfp);
    }
}


char rpmPath[1024];
char uninsPath[1024];
GtkWidget *gButton;
GtkWidget *window;
GtkWidget *scrolled_window;
GtkWidget *label;
GtkWidget *label_agree;
GtkWidget *fixed;
GtkWidget *vbox;
GtkWidget *check_button;
GtkWidget *check_fixed;    
GtkWidget *button_license;     //许可协议
GtkWidget *button_privacy;     //隐私协议
GSList *group;
GtkTextBuffer *text_buffer;
GtkWidget *text_view;
GtkTextIter *text_iter;

void buttonClickedlicense( GtkWidget *widget,
                    gpointer   data );

void buttonClickedprivacy( GtkWidget *widget,
                    gpointer   data );

void buttonClicked( GtkWidget *widget,
                    gpointer   data );
void checkButtonClicked( GtkWidget *widget,
                    gpointer   data );
void destroy( GtkWidget *widget,
              gpointer   data )
{
    gtk_main_quit ();
}

gint delete_event( GtkWidget *widget,
                   GdkEvent  *event,
                   gpointer   data )
{
    /* 如果你的 "delete_event" 信号处理函数返回 FALSE，GTK 会发出 
"destroy" 信号。
     * 返回 TRUE，你不希望关闭窗口。
     * 当你想弹出“你确定要退出吗?”对话框时它很有用。*/

    g_print ("delete event occurred\n");

    /* 改 TRUE 为 FALSE 程序会关闭。*/

    return FALSE;
}

void initRPMPath()
{
    //printf("OS_BITS =%lu\n", OS_BITS);
    char path[1024];
    getcwd(path, sizeof(path));                 // 获取程序路径

    struct dirent *pDirEntry = NULL;
    DIR          *pDir      = NULL;
    if( (pDir = opendir(path)) == NULL )
    {
        // 路过为找到路径时,退出
        printf("opendir failed!\n");
        return ;
    }
    else
    {
        char * pTail = rpmPath;
        while( pDirEntry = readdir(pDir) )                                  // 获取目录中的文件
        {
            const char *matchStr = OS_BITS == 32? "i386.deb": "64.deb";     // 获取系统位数,匹配对应的安装包
		    if (strstr(pDirEntry->d_name, matchStr))                        // 想到相应的包名时
            {
                //printf("索引节点:%d\t 偏移量：%d\t 文件名长：%d\t文件类型：%d\t 文件名：%s\n",
                //pDirEntry->d_ino, pDirEntry->d_off,
                //pDirEntry->d_reclen,pDirEntry->d_type,pDirEntry->d_name);
                int writeSize;
                writeSize = snprintf(pTail, sizeof(rpmPath), "\"%s/%s\" ", path, pDirEntry->d_name); // 获取到安装包名称的全路径
                pTail += writeSize;
            }
        }
        closedir(pDir);
        return ;   
    }
}


void initUninsPath()
{
    char path[1024];
    getcwd(path, sizeof(path));

    struct dirent *pDirEntry = NULL;
    DIR          *pDir      = NULL;
    if( (pDir = opendir(path)) == NULL )
    {
        printf("opendir failed!\n");
        return ;
    }
    else
    {
        char * pTail = uninsPath;
        while( pDirEntry = readdir(pDir) )
        {
            const char *matchStr = "uninstall";
		    if (strstr(pDirEntry->d_name, matchStr))
            {
                //printf("索引节点:%d\t 偏移量：%d\t 文件名长：%d\t文件类型：%d\t 文件名：%s\n",
                //pDirEntry->d_ino, pDirEntry->d_off,
                //pDirEntry->d_reclen,pDirEntry->d_type,pDirEntry->d_name);
                int writeSize;
                writeSize = snprintf(pTail, sizeof(uninsPath), "\"%s/%s\" ", path, pDirEntry->d_name);
                pTail += writeSize;
            }
        }
        closedir(pDir);
        return ;    
    } 
}

void initAndShowInstallWindow()
{
    char *language = getenv("LANG");            // 获取系统语言
    /* Create the main window */
    // 创建主窗口
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);                          // 创建新窗口,类型为window
    gtk_window_set_title(GTK_WINDOW(window), str_processName);              // 设置标题
    gtk_widget_set_size_request(GTK_WIDGET(window), 500, 470);              // 设置主窗口的长宽
    gtk_window_set_resizable(GTK_WINDOW(window), false);                    // 设置不允许用户调整大小
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);        // 设置位置约束
    gtk_container_set_border_width (GTK_CONTAINER (window), 15);            // 设置边框宽度
 
    /* Set up the delete_event's callback, passing data(NULL) to the callback func*/
    g_signal_connect (G_OBJECT (window), "delete_event",
                      G_CALLBACK (delete_event), NULL);



    /* destroy() would be called in gtk_widget_destroy() or after delete_event's callback func(return YES required) */
    g_signal_connect (G_OBJECT (window), "destroy",
                      G_CALLBACK (destroy), NULL);


    /* Create the label*/
    // str_noticeLabel = 请仔细阅读下列许可协议，您在安装前必须同意这些协议条款。
    label = gtk_label_new(str_noticeLabel);                                 // 创建新窗口,类型为label

    gtk_widget_set_size_request(GTK_WIDGET(label), 470, -1);                // 设置主窗口的长宽
    gtk_misc_set_alignment(GTK_MISC(label), 0, 0 );                         // 获取窗口的对齐方式
    PangoFontDescription *font_desc = pango_font_description_from_string("12");   //设置字体样式
    //pango_font_description_set_size (font_desc, 50 * PANGO_SCALE); // 这里的“50”就是你的字体大小，可以随意设置。
    gtk_widget_modify_font(GTK_WIDGET(label), font_desc);           // 设置字体

    pango_font_description_free (font_desc);                        // 释放字体说明
    
    gtk_label_set_line_wrap(GTK_LABEL(label), true);                        // 设置是否换行
    gtk_label_set_line_wrap_mode(GTK_LABEL(label), PANGO_WRAP_WORD);        // 设置自动换行
    
    GtkRequisition labelSize;
    gtk_widget_size_request(GTK_WIDGET(label), &labelSize);
    gtk_widget_set_size_request(GTK_WIDGET(label), labelSize.width, labelSize.height+15);
    
    // 我同意《最终用户许可协议》和《隐私政策》
    label_agree = gtk_label_new(str_checkButton);                                 // 创建新窗口,类型为label
    if (strstr(language,"ar_EG.UTF-8") || strstr(language,"he_IL.UTF-8"))
    {
        gtk_widget_set_size_request(GTK_WIDGET(label_agree), 390, -1);            // 设置主窗口的长宽
    }
    else
    {
        gtk_widget_set_size_request(GTK_WIDGET(label_agree), 440, -1);            // 设置主窗口的长宽
    }
    
    gtk_label_set_line_wrap(GTK_LABEL(label_agree), true);                        // 设置是否换行
    gtk_label_set_line_wrap_mode(GTK_LABEL(label_agree), PANGO_WRAP_WORD);        // 设置自动换行
    GtkRequisition labelagreeSize;
    gtk_widget_size_request(GTK_WIDGET(label_agree), &labelagreeSize);
    gtk_widget_set_size_request(GTK_WIDGET(label_agree), labelagreeSize.width, labelagreeSize.height+15);

    /* Create the install(cancle) button */
    gButton = gtk_button_new_with_label (str_installButton);
    GtkRequisition buttonSize;
    gtk_widget_size_request(GTK_WIDGET(gButton), &buttonSize);
    if(buttonSize.width < 50)
    {
	    gtk_widget_set_size_request(GTK_WIDGET(gButton), 50, -1);
        buttonSize.width = 50;
    }
    fixed = gtk_fixed_new();
    vbox = gtk_vbox_new(false, 0);
    // 阿拉伯语与希伯来语 安装按钮靠左边显示
    if (strstr(language,"ar_EG.UTF-8") || strstr(language,"he_IL.UTF-8"))
    {
        gtk_fixed_put(GTK_FIXED(fixed), gButton, 10,10);
    }
    else
    {
        gtk_fixed_put(GTK_FIXED(fixed), gButton, 460-buttonSize.width,10);
    }
    
    gtk_widget_set_sensitive (GTK_WIDGET(gButton), false);
    g_signal_connect (G_OBJECT (gButton), "clicked",
                      G_CALLBACK (buttonClicked), NULL);

    /* Create the check button*/
    // str_checkButton = 我同意
    //check_button = gtk_check_button_new_with_label(str_checkButton);
    check_button = gtk_check_button_new();
    GtkRequisition checkButtonSize;
    gtk_widget_size_request(GTK_WIDGET(check_button), &checkButtonSize);

    gtk_button_set_focus_on_click(GTK_BUTTON(check_button), false);
    g_signal_connect (G_OBJECT (check_button), "clicked",
                      G_CALLBACK (checkButtonClicked), NULL);   

    check_fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(check_button), label_agree);
    //gtk_fixed_put(GTK_FIXED(check_fixed), check_button, 0,-1*(buttonSize.height - checkButtonSize.height)/2 - checkButtonSize.height);
    if (strstr(language,"ar_EG.UTF-8") || strstr(language,"he_IL.UTF-8"))
    {
        gtk_fixed_put(GTK_FIXED(check_fixed), check_button, 54,0);
    }
    else
    {
        gtk_fixed_put(GTK_FIXED(check_fixed), check_button, 0,0);
    }
    

    /* Create the text view*/
    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), false);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(text_view), false);
    text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));

    gtk_text_buffer_set_text(text_buffer, licenseData, licenseDataSize);
    gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(scrolled_window), GTK_SHADOW_IN);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD);
    gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);
    gtk_widget_set_size_request(GTK_WIDGET(scrolled_window), 470, 390-labelSize.height - 15 - buttonSize.height - 15);

    button_license = gtk_radio_button_new_with_label(NULL,str_Button_license);
    g_signal_connect (G_OBJECT (button_license), "clicked",
                      G_CALLBACK (buttonClickedlicense), NULL);

    group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(button_license));
    button_privacy = gtk_radio_button_new_with_label(group,str_Button_privacy);
    g_signal_connect (G_OBJECT (button_privacy), "clicked",
                      G_CALLBACK (buttonClickedprivacy), NULL);

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button_license),TRUE);

    //gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, true, 0);
    gtk_box_pack_start(GTK_BOX(vbox), scrolled_window, FALSE, true, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button_license,FALSE,true,0);
    gtk_box_pack_start(GTK_BOX(vbox), button_privacy,FALSE,true,0);
    gtk_box_pack_start(GTK_BOX(vbox), check_fixed, FALSE, true, 0);
    gtk_box_pack_start(GTK_BOX(vbox), fixed, FALSE, true, 0);

    /* Add the container to window and show up */
    gtk_container_add (GTK_CONTAINER (window), vbox);

    gtk_widget_show (check_fixed);
    gtk_widget_show (label);
    gtk_widget_show (label_agree);
    gtk_widget_show (scrolled_window);
    gtk_widget_show (text_view);

    gtk_widget_show (gButton);
    gtk_widget_show (check_button);
    gtk_widget_show (fixed);
    gtk_widget_show (vbox);
    gtk_widget_show (button_license);
    gtk_widget_show (button_privacy);
    gtk_widget_show (window);
}

void deallocInstallWindow()
{
    gtk_widget_hide (vbox);
    gtk_container_remove (GTK_CONTAINER(window), GTK_WIDGET(vbox));
}
void initAndshowInstallSucceededWindow()
{
    GtkWidget *boldLabel;
    GtkWidget *boldLabelFixed;
    GtkWidget *doneButton;
    GtkWidget *doneButtonFixed;
    GtkWidget *newVBox;

    /* Create done button*/
    // 创建完成按钮
    doneButton = gtk_button_new_with_label (str_doneButton);
    doneButtonFixed = gtk_fixed_new();
    GtkRequisition doneButtonSize;
    gtk_widget_size_request(GTK_WIDGET(doneButton), &doneButtonSize);
    if(doneButtonSize.width < 50)
    {
	    gtk_widget_set_size_request(GTK_WIDGET(doneButton), 50, -1);
        doneButtonSize.width = 50;
    }
    gtk_fixed_put(GTK_FIXED(doneButtonFixed), doneButton, 470-doneButtonSize.width,60);
    //gtk_widget_set_sensitive (GTK_WIDGET(doneButton), false);
    g_signal_connect (G_OBJECT (doneButton), "clicked",
                      G_CALLBACK (destroy), NULL);


    /* Create bold label*/
    // 创建粗体标签(安装完成)
    boldLabel = gtk_label_new(str_finishLabel);
    PangoFontDescription *font_desc_bold = pango_font_description_from_string("12");
    pango_font_description_set_size (font_desc_bold, 26 * PANGO_SCALE); // 这里的“50”就是你的字体大小，可以随意设置。
    gtk_widget_modify_font(GTK_WIDGET(boldLabel), font_desc_bold);
    pango_font_description_free (font_desc_bold);
    gtk_misc_set_alignment(GTK_MISC(boldLabel), 0.5, 0.5);
    //gtk_label_set_line_wrap(GTK_LABEL(boldLabel), true);
    //gtk_label_set_line_wrap_mode(GTK_LABEL(boldLabel), PANGO_WRAP_WORD);
    gtk_widget_set_size_request(GTK_WIDGET(boldLabel), 470, 390 - doneButtonSize.height - 15);
    GtkRequisition boldLabelSize;
    gtk_widget_size_request(GTK_WIDGET(boldLabel), &boldLabelSize);

    boldLabelFixed = gtk_fixed_new();

    /* Create the vbox*/
    newVBox = gtk_vbox_new(false, 0);
    gtk_box_pack_start(GTK_BOX(newVBox), boldLabel, FALSE, true, 0);
    gtk_box_pack_start(GTK_BOX(newVBox), doneButtonFixed, FALSE, true, 0);

    /* Add the container to window and show up */
    gtk_container_add (GTK_CONTAINER (window), newVBox);
    
    gtk_widget_show (boldLabel);
    gtk_widget_show (doneButton);
    gtk_widget_show (doneButtonFixed);
    gtk_widget_show (newVBox);

    gtk_widget_grab_focus(GTK_WIDGET(doneButton));
}
void deallocInstallSucceededWindow()
{
return;
}

/* 这是一个回调函数。data 参数在本示例中被忽略。#include <gksu-polkit/gksu-polkit.h>
#include <gksu-polkit/gksu-process.h>
* 后面有更多的回调函数示例。*/
void buttonClicked( GtkWidget *widget,
                    gpointer   data )
{
    char cmd[1024];
    snprintf(cmd, sizeof(cmd), "pkexec sudo %s ", uninsPath);   // 将卸载脚本路径传入,提示用户输入密码
    int err = system(cmd);                                      // 使用system函数运行shell命令
    printf("system return %d\n", err);                          // 输出返回值
  
    if(err==0)  // 返回值0表示卸载成功
    {
        deallocInstallWindow();     // 安装窗口
        initAndshowInstallSucceededWindow();    // 初始化并且显示安装成功的界面
    }
}

void checkButtonClicked( GtkWidget *widget,
                    gpointer   data )
{
  bool isAgreed = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
  gtk_widget_set_sensitive (GTK_WIDGET(gButton), isAgreed);
  
  if (isAgreed){
      gtk_widget_grab_focus(GTK_WIDGET(gButton));
  }

}

void buttonClickedprivacy( GtkWidget *widget,
                        gpointer   data )
{
    text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_text_buffer_set_text(text_buffer, privacyData, privacyDataSize);    // 更换内容
}

void buttonClickedlicense( GtkWidget *widget,
                        gpointer   data )
{
    text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_text_buffer_set_text(text_buffer, licenseData, licenseDataSize);    // 更换内容
}


int main( int   argc,
          char *argv[] )
{
    initialzeLocalStrings();    // 初始化本地化字符串
    gtk_init (&argc, &argv);    // 初始化gtk参数
    initRPMPath();              // 找到安装包的位置
    initUninsPath();            // 找到卸载脚本的位置

    
    initAndShowInstallWindow(); // 初始化并显示安装窗口
    gtk_main ();
    return 0;
} 
