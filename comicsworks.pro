TEMPLATE = subdirs

SUBDIRS += \
    features/step_definitions \
#    comics/works/gui \
#    comics/works/entities \
#    comics/works/usecases \
    comics/works/solutions/studio

DISTFILES += features/*.feature \
    features/describe_panel.feature
