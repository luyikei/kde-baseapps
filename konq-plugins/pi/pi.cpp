#include "pi.h"
#include <kparts/part.h>
#include <kactioncollection.h>
#include <klocale.h>
#include <kmessagebox.h>
#include <kapplication.h>
#include <kpluginfactory.h>

Pi::Pi( QObject* parent, const QVariantList & )
    : KParts::Plugin( parent )
{

    KAction *action = actionCollection()->addAction("calculatepi");
    action->setText(i18n( "&Calculate Pi..." ));
    connect(action, SIGNAL(triggered(bool)), SLOT(calcPi()));
}

void Pi::calcPi()
{
    KParts::ReadOnlyPart * part = qobject_cast<KParts::ReadOnlyPart *>(parent());
    int count=0;
    const int total = 100000;
    qreal pi=0;

    for (int i=0; i<total; i++) {
        qreal x = (qreal)qrand() / (RAND_MAX);
        qreal y = (qreal)qrand() / (RAND_MAX);

        if (x*x+y*y <= 1) {
            count++;
        }
    }

    pi = (qreal)count / (qreal)total * 4.0;

    KMessageBox::sorry(part->widget(),i18n("%1").arg(pi));
}

K_PLUGIN_FACTORY(KonqPiFactory, registerPlugin<Pi>();)
K_EXPORT_PLUGIN(KonqPiFactory("pi"))

#include "pi.moc"

