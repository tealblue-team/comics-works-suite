TEMPLATE = subdirs

SUBDIRS += \
    features/step_definitions \
    comics/works/ui \
    comics/works/entities \
    comics/works/usecases \
    comics/works/solutions/studio \
    comics/works/adapters \
    comics/works/utils

DISTFILES += \
    features/*.feature \
    features/upcoming/*.feature \
    samples/project/heavyLoad1.cw.json \
    samples/storyboard/heavyLoad1.storyboard.cw.pdf
