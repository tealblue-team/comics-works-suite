TEMPLATE = subdirs

SUBDIRS += \
    features/step_definitions \
    comics/works/ui \
    comics/works/entities \
    comics/works/usecases \
    comics/works/solutions/studio \
    comics/works/adapters

DISTFILES += features/*.feature \
    features/name_panel.feature
