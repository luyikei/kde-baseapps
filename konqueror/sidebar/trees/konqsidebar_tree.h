#ifndef KONQSIDEBAR_TREE_H
#define KONQSIDEBAR_TREE_H

#include <konqsidebarplugin.h>
#include <QtGui/QLabel>
#include <QtGui/QLayout>
#include <kparts/part.h>
#include <kparts/factory.h>
#include <kparts/browserextension.h>
#include <kdialog.h>
#include <QtGui/QComboBox>
#include <QtCore/QStringList>
#include <klocale.h>
#include <QtGui/QLineEdit>

class KonqSidebarTree;

class KonqSidebar_Tree: public KonqSidebarModule
        {
                Q_OBJECT
                public:
                KonqSidebar_Tree(const KComponentData &componentData, QWidget *parent,
                                 const QString &desktopName_, const KConfigGroup& configGroup);
                ~KonqSidebar_Tree();
                virtual QWidget *getWidget();
                protected:
                        class QWidget *widget;
                        class KonqSidebarTree *tree;
                        virtual void handleURL(const KUrl &url);
		protected Q_SLOTS:
			void copy();
			void cut();
			void paste();
			void trash();
			void del();
			void rename();
Q_SIGNALS:
			void popupMenu( const QPoint &global, const KUrl &url,
					const QString &mimeType, mode_t mode = (mode_t)-1 );
			void popupMenu( const QPoint &global, const KFileItemList &items );
			void enableAction( const char * name, bool enabled );
        };

#endif // KONQSIDEBAR_TREE_H
